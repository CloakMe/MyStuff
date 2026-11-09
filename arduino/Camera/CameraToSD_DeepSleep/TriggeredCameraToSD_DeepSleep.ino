/*
  TriggeredCameraToSD_DeepSleep
  ------------------------------
  The board deep-sleeps between events. A PIR sensor wakes it (ext0
  wakeup), it takes ONE photo, saves it to the SD card, then goes back
  to sleep. Stops after NUM_CAPTURES photos.

  Board: AI-Thinker ESP32-CAM

  How deep sleep changes the program flow:
    - Every wake is a fresh boot: setup() runs each time, loop() never does.
    - Values that must survive sleep live in RTC_DATA_ATTR variables.
      They survive deep sleep but reset on power loss or the reset button.

  PIR wiring (HC-SR501 or similar):
    PIR VCC -> 5V pin
    PIR GND -> GND
    PIR OUT -> GPIO13   (must be an RTC GPIO; GPIO3 can NOT wake from deep sleep)

  Notes:
    - Keep the SD card in 1-bit mode (as below); GPIO13 is also the card's
      DAT3 line, which 1-bit mode does not use.
    - Remember camera_pins.h must sit in the same sketch folder.
*/

#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"

// ===================
// Select camera model
// ===================
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// ===========================
// User configuration
// ===========================
#define TRIGGER_PIN                 13     // must be an RTC-capable GPIO for ext0 wakeup
#define TRIGGER_ACTIVE_LEVEL         1     // 1 = sensor drives HIGH on motion, 0 = LOW
#define NUM_CAPTURES                10     // how many photos to take in total (n)

#define PIR_WARMUP_MS            30000     // PIR needs ~30-60 s to settle after power-up (power-on only).
                                           // Set to 0 while testing without a real PIR.
#define SENSOR_IDLE_WAIT_MS      10000     // after a photo, wait up to this long for the PIR output to fall
#define RECHECK_SLEEP_S              5     // if the PIR is STILL active, nap this long and check again
#define WARMUP_FRAMES                3     // frames discarded after waking so exposure/white balance settle
#define CAPTURE_ON_POWER_ON          0     // 1 = also take a photo on power-on/reset (handy for testing)
#define POWER_DOWN_CAMERA_IN_SLEEP   1     // 1 = hold the camera's PWDN pin high during sleep to save power

// Persist across deep sleep (reset on power loss / reset button)
RTC_DATA_ATTR int captureCount  = 0;   // photos taken this session
RTC_DATA_ATTR int nextFileIndex = 1;   // next img_XXXX number to try

// ---------------------------
// Camera init
// ---------------------------
bool initCamera() {
  camera_config_t config = {};          // zero-init so no field is left as garbage
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn  = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size   = FRAMESIZE_QVGA;  // QVGA is small/fast; UXGA is the largest
  config.jpeg_quality = 15;
  config.fb_count     = 1;
  config.grab_mode    = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location  = CAMERA_FB_IN_PSRAM;

  if (psramFound()) {
    config.jpeg_quality = 10;
    config.fb_count = 2;
    config.grab_mode = CAMERA_GRAB_LATEST;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.fb_location = CAMERA_FB_IN_DRAM;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed, error 0x%x\n", err);
    return false;
  }

  sensor_t *s = esp_camera_sensor_get();
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);
    s->set_brightness(s, 1);
    s->set_saturation(s, -2);
  }
  return true;
}

// ---------------------------
// SD card init
// ---------------------------
bool initSD() {
  // The mount point is given ONLY here; every other SD_MMC path is relative to it.
  if (!SD_MMC.begin("/sdcard", true)) {   // true = 1-bit mode
    Serial.println("SD card mount failed");
    return false;
  }
  if (SD_MMC.cardType() == CARD_NONE) {
    Serial.println("No SD card detected");
    return false;
  }
  return true;
}

// ---------------------------
// File naming: never overwrite an existing photo, even after a reset
// ---------------------------
String pathFor(int index) {
  char p[24];
  snprintf(p, sizeof(p), "/img_%04d.jpg", index);
  return String(p);
}

int findFreeIndex(int start) {
  int i = start;
  while (SD_MMC.exists(pathFor(i))) i++;
  return i;
}

// ---------------------------
// Capture one frame and write it to the SD card
// ---------------------------
bool captureAndSave() {
  // After waking, the sensor's auto-exposure needs a few frames to settle;
  // the first frames are often dark or tinted, so throw them away.
  for (int i = 0; i < WARMUP_FRAMES; i++) {
    camera_fb_t *tmp = esp_camera_fb_get();
    if (tmp) esp_camera_fb_return(tmp);
  }

  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return false;
  }

  nextFileIndex = findFreeIndex(nextFileIndex);
  String path = pathFor(nextFileIndex);

  File file = SD_MMC.open(path.c_str(), FILE_WRITE);
  if (!file) {
    Serial.printf("Failed to open %s for writing\n", path.c_str());
    esp_camera_fb_return(fb);
    return false;
  }

  size_t len = fb->len;
  size_t written = file.write(fb->buf, len);
  file.close();
  esp_camera_fb_return(fb);

  if (written != len) {
    Serial.printf("Short write to %s (%u of %u bytes)\n", path.c_str(), (unsigned)written, (unsigned)len);
    return false;
  }

  Serial.printf("Saved %s (%u bytes)\n", path.c_str(), (unsigned)len);
  nextFileIndex++;
  return true;
}

// ---------------------------
// Sleep helpers
// ---------------------------
void releaseSleepHolds() {
#if POWER_DOWN_CAMERA_IN_SLEEP
  // The PWDN pin was held high during sleep; release it so the camera driver can control it again
  if (PWDN_GPIO_NUM >= 0) rtc_gpio_hold_dis((gpio_num_t)PWDN_GPIO_NUM);
#endif
}

void powerDownCameraForSleep() {
#if POWER_DOWN_CAMERA_IN_SLEEP
  if (PWDN_GPIO_NUM >= 0) {
    pinMode(PWDN_GPIO_NUM, OUTPUT);
    digitalWrite(PWDN_GPIO_NUM, HIGH);              // HIGH = camera powered down
    rtc_gpio_hold_en((gpio_num_t)PWDN_GPIO_NUM);    // keep it HIGH while asleep
  }
#endif
}

bool waitForSensorIdle(unsigned long timeoutMs) {
  unsigned long start = millis();
  while (digitalRead(TRIGGER_PIN) == TRIGGER_ACTIVE_LEVEL) {
    if (millis() - start >= timeoutMs) return false;
    delay(50);
  }
  return true;
}

void armTriggerAndSleep() {
  esp_sleep_enable_ext0_wakeup((gpio_num_t)TRIGGER_PIN, TRIGGER_ACTIVE_LEVEL);

  // Hold the pin at its idle level with an internal resistor, so a
  // disconnected/floating sensor wire can't cause false wake-ups.
  if (TRIGGER_ACTIVE_LEVEL) {
    rtc_gpio_pullup_dis((gpio_num_t)TRIGGER_PIN);
    rtc_gpio_pulldown_en((gpio_num_t)TRIGGER_PIN);
  } else {
    rtc_gpio_pulldown_dis((gpio_num_t)TRIGGER_PIN);
    rtc_gpio_pullup_en((gpio_num_t)TRIGGER_PIN);
  }

  Serial.println("Deep sleep - waiting for sensor trigger...");
  Serial.flush();
  powerDownCameraForSleep();
  esp_deep_sleep_start();
}

void sleepAndRecheck() {
  esp_sleep_enable_timer_wakeup((uint64_t)RECHECK_SLEEP_S * 1000000ULL);
  Serial.flush();
  powerDownCameraForSleep();
  esp_deep_sleep_start();
}

// ---------------------------
// Setup - runs on every wake; loop() is never reached
// ---------------------------
void setup() {
  // Disable brownout detector - camera current spikes can otherwise reset some boards
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  delay(100);
  Serial.println();

  releaseSleepHolds();
  pinMode(TRIGGER_PIN, INPUT);

  bool shouldCapture = false;
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

  if (cause == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Woken by sensor trigger.");
    shouldCapture = true;
  } else if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    Serial.println("Timer wake: re-checking sensor.");
  } else {
    Serial.println("Power-on / reset boot.");
    if (PIR_WARMUP_MS > 0) {
      Serial.printf("Letting the PIR settle for %d s...\n", PIR_WARMUP_MS / 1000);
      delay(PIR_WARMUP_MS);
    }
    shouldCapture = CAPTURE_ON_POWER_ON;
  }

  if (shouldCapture) {
    if (initCamera() && initSD()) {
      if (captureAndSave()) captureCount++;
      Serial.printf("Photos so far: %d of %d\n", captureCount, NUM_CAPTURES);
    } else {
      Serial.println("Init failed this cycle; will retry on the next trigger.");
    }
    esp_camera_deinit();
    SD_MMC.end();
  }

  if (captureCount >= NUM_CAPTURES) {
    Serial.println("All photos taken. Sleeping indefinitely (reset to start again).");
    Serial.flush();
    powerDownCameraForSleep();
    esp_deep_sleep_start();   // no wake source armed -> stays asleep
  }

  // PIR modules hold OUT high for a few seconds. If we armed the wakeup
  // while it's still high, we'd wake instantly and take duplicate photos.
  if (!waitForSensorIdle(SENSOR_IDLE_WAIT_MS)) {
    Serial.println("Sensor still active - napping, will re-check.");
    sleepAndRecheck();
  }

  armTriggerAndSleep();
}

void loop() {
  // never reached
}

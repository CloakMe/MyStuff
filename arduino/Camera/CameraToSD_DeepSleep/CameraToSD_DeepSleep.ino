/*
  TriggeredCameraToSD_DeepSleep
  ------------------------------
  Power-efficient version: the board deep-sleeps between events and is
  woken by an external trigger (e.g. a PIR sensor) via ext0 wakeup.
  On each wake caused by the trigger, it captures one JPEG and saves it
  to the SD card, then goes back to sleep. Stops after NUM_CAPTURES
  images.

  Board: AI-Thinker ESP32-CAM

  IMPORTANT - deep sleep means setup() runs on every wake; loop() is
  never used. Anything that must survive across sleeps (like the
  capture counter) is stored in RTC memory via RTC_DATA_ATTR, which
  survives deep sleep but resets to 0 on power loss or a manual reset.

  Wiring for the trigger:
    - Sensor/button output -> GPIO13 (an RTC-capable GPIO, required for ext0).
    - Set TRIGGER_ACTIVE_LEVEL to 1 (HIGH) for a typical PIR module,
      or 0 (LOW) for a button wired to GND with an internal pull-up.
    - PIR modules are usually 5V-logic on their OUT pin; use a divider
      or level shifter to GPIO13, or power the PIR from 3.3V if it
      supports that (check your module's datasheet).

  Why GPIO13: SD_MMC is used in 1-bit mode here (CLK=14, CMD=15, D0=2),
  which leaves GPIO4, 12 and 13 free for other use.
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
#define TRIGGER_PIN              13     // must be an RTC-capable GPIO for ext0
#define TRIGGER_ACTIVE_LEVEL      1     // 1 = HIGH, 0 = LOW
#define NUM_CAPTURES              10    // how many images to capture in total (n)
#define PIR_RESET_TIMEOUT_MS   30000    // give up waiting for sensor to reset after this long
#define PIR_RESET_POLL_MS         50

// Persists across deep sleep (NOT across power loss / manual reset)
RTC_DATA_ATTR int captureCount = 0;

// ---------------------------
// Camera init
// ---------------------------
bool initCamera() {
  camera_config_t config;
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
  config.xclk_freq_hz = 20000000;
  config.pixel_format  = PIXFORMAT_JPEG;
  config.frame_size    = FRAMESIZE_UXGA;
  config.jpeg_quality   = 12;
  config.fb_count       = 1;

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
  if (!SD_MMC.begin("/sdcard", true)) { // 1-bit mode
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
// Capture one frame and write it to the SD card
// ---------------------------
bool captureAndSave(int index) {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return false;
  }

  char path[40];
  snprintf(path, sizeof(path), "/sdcard/img_%04d.jpg", index);

  File file = SD_MMC.open(path, FILE_WRITE);
  if (!file) {
    Serial.printf("Failed to open %s for writing\n", path);
    esp_camera_fb_return(fb);
    return false;
  }

  file.write(fb->buf, fb->len);
  file.close();
  esp_camera_fb_return(fb);

  Serial.printf("Saved %s (%u bytes)\n", path, fb->len);
  return true;
}

// ---------------------------
// Arm ext0 wakeup on the trigger pin and deep sleep
// ---------------------------
void armTriggerAndSleep() {
  esp_sleep_enable_ext0_wakeup((gpio_num_t)TRIGGER_PIN, TRIGGER_ACTIVE_LEVEL);
  Serial.println("Arming trigger and entering deep sleep...");
  Serial.flush();
  esp_deep_sleep_start();
  // execution never returns from here
}

// ---------------------------
// Setup - runs fresh on every wake, since loop() is never used
// ---------------------------
void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector
  Serial.begin(115200);
  delay(100);
  Serial.println();

  pinMode(TRIGGER_PIN, INPUT);

  // All captures already done on a previous cycle: stay asleep for good
  if (captureCount >= NUM_CAPTURES) {
    Serial.println("All captures already complete. Sleeping indefinitely.");
    esp_deep_sleep_start(); // no wakeup source armed -> sleeps forever
  }

  esp_sleep_wakeup_cause_t wakeReason = esp_sleep_get_wakeup_cause();

  if (wakeReason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Woken by trigger.");

    bool ok = initCamera() && initSD();
    if (ok) {
      captureCount++;
      Serial.printf("Trigger #%d of %d\n", captureCount, NUM_CAPTURES);
      if (!captureAndSave(captureCount)) {
        captureCount--; // capture failed - retry this index next trigger
      }
    } else {
      Serial.println("Init failed this cycle; will retry on next trigger.");
    }

    esp_camera_deinit(); // release the camera before sleeping again
  } else {
    Serial.println("Power-on / reset boot. Arming trigger, no photo taken.");
  }

  if (captureCount >= NUM_CAPTURES) {
    Serial.println("All captures complete. Sleeping indefinitely.");
    esp_deep_sleep_start();
  }

  // Wait for the sensor to de-assert before re-arming, so the board
  // doesn't instantly wake again on the same still-active event
  unsigned long start = millis();
  while (digitalRead(TRIGGER_PIN) == TRIGGER_ACTIVE_LEVEL &&
         millis() - start < PIR_RESET_TIMEOUT_MS) {
    delay(PIR_RESET_POLL_MS);
  }

  armTriggerAndSleep();
}

void loop() {
  // never reached - setup() always ends by going back to deep sleep
}

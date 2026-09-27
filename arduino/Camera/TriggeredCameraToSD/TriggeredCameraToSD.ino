/*
  TriggeredCameraToSD
  --------------------
  On each external trigger event, captures one JPEG frame from the
  ESP32-CAM and saves it to the SD card. Repeats until NUM_CAPTURES
  images have been saved, then stops.

  Board: AI-Thinker ESP32-CAM (has an onboard microSD slot)

  Wiring for the trigger:
    - Connect your sensor / button output to TRIGGER_PIN (GPIO13).
    - If using a simple push button: button -> GPIO13, other side -> GND,
      and set TRIGGER_ACTIVE_STATE to LOW, pinMode to INPUT_PULLUP (see setup()).
    - If using a PIR or other active-HIGH sensor: leave defaults as-is.

  Why GPIO13: SD_MMC is used in 1-bit mode here (CLK=14, CMD=15, D0=2),
  which leaves GPIO4, 12 and 13 free. In the default 4-bit SD_MMC mode
  those pins are reserved for the card and are NOT safe to reuse.
*/

#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

// ===================
// Select camera model
// ===================
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// ===========================
// User configuration
// ===========================
#define TRIGGER_PIN            13     // digital input for the event trigger
#define TRIGGER_ACTIVE_STATE    HIGH  // HIGH for most PIR modules; LOW for a button to GND
#define NUM_CAPTURES            10    // how many images to capture in total (n)
#define DEBOUNCE_MS              50   // confirm the trigger is still active after this delay
#define COOLDOWN_MS            2000   // minimum time between captures, to avoid double-firing

// ===========================
// State
// ===========================
static int captureCount = 0;

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
  config.xclk_freq_hz = 10000000;
  config.pixel_format  = PIXFORMAT_JPEG;   // JPEG is what we write straight to a file
  config.frame_size    = FRAMESIZE_QVGA; // FRAMESIZE_QVGA is lower quality; FRAMESIZE_UXGA is higher
  config.jpeg_quality   = 15;
  config.fb_count       = 1;

  if (psramFound()) {
    config.jpeg_quality = 10;
    config.fb_count = 2;
    config.grab_mode = CAMERA_GRAB_LATEST;
  } else {
    // Limit frame size when PSRAM is not available
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
  // "true" = 1-bit mode, which frees GPIO4/12/13 for other use
  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("SD card mount failed");
    return false;
  }

  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card detected");
    return false;
  }

  Serial.printf("SD card mounted, size: %lluMB\n", SD_MMC.cardSize() / (1024 * 1024));
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
// Setup
// ---------------------------
void setup() {
  
  // Disable brownout detector - the camera's current draw can otherwise
  // reset the board on some ESP32-CAM units
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  Serial.println();

  // Use INPUT_PULLUP + TRIGGER_ACTIVE_STATE = LOW for a plain push button to GND.
  // Use plain INPUT for an active-HIGH sensor module (PIR, IR break-beam, etc.)
  
  // pinMode(TRIGGER_PIN, INPUT);
  
  if (!initCamera()) {
    Serial.println("Halting: camera init failed");
    while (true) delay(1000);
  }

  if (!initSD()) {
    Serial.println("Halting: SD init failed");
    while (true) delay(1000);
  }
  pinMode(TRIGGER_PIN, INPUT_PULLDOWN);
  captureAndSave(1);
  Serial.printf("Ready. Waiting for %d trigger events on GPIO%d...\n", NUM_CAPTURES, TRIGGER_PIN);
}

// ---------------------------
// Main loop
// ---------------------------
void loop() {
  if (captureCount >= NUM_CAPTURES) {
    Serial.println("All captures complete. Idling.");
    delay(5000);
    return;
  }

  if (digitalRead(TRIGGER_PIN) == TRIGGER_ACTIVE_STATE) {
    // Debounce: confirm the signal is still active a moment later
    delay(DEBOUNCE_MS);
    if (digitalRead(TRIGGER_PIN) == TRIGGER_ACTIVE_STATE) {
      captureCount++;
      Serial.printf("Trigger #%d of %d detected\n", captureCount, NUM_CAPTURES);

      if (!captureAndSave(captureCount)) {
        // Don't consume a slot on failure - retry this index next time
        captureCount--;
      }

      // Wait out the sensor/bounce before watching for the next event
      delay(COOLDOWN_MS);
    }
  }
}

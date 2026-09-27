#include "esp_camera.h"
#include <WiFi.h>

//
// Minimal hardware test:
// - connects to WiFi (optional but helps print IP)
// - initializes camera
// - captures a few frames and prints frame size / errors
//

// ---------- USER SETTINGS ----------
const char* WIFI_SSID = "Radina";
const char* WIFI_PASS = "korona15";
// ---------------------------------

// Common ESP32-CAM AI-Thinker pinout (adjust only if your board differs)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM     22

// Try changing this to match your sensor if your code/library supports it.
// Many people need to adjust this section for OV5640 boards.
static camera_config_t makeCameraConfig() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

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
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  // Clock & pixel format
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Frame size/buffering
  config.frame_size = FRAMESIZE_QVGA; // 320x240
  config.grab_mode = CAMERA_GRAB_LATEST;

  // If the board supports it, using 2 framebuffers can help.
  config.fb_count = 1;

  return config;
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n=== ESP32-CAM Camera Hardware Test ===");
  delay(2000);
  // Optional WiFi (not required for camera init)
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting WiFi");
  for (int i = 0; i < 20 && WiFi.status() != WL_CONNECTED; i++) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected, IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi not connected (continuing anyway).");
  }

  camera_config_t config = makeCameraConfig();

  // Initialize camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.print("Camera init FAILED. esp_err=");
    Serial.println((int)err);
    Serial.println("Most common causes: wrong sensor/pin mapping for your ESP32-CAM variant.");
    while (true) { delay(1000); }
  }

  Serial.println("Camera init SUCCESS.");

  // Capture a few frames
  for (int i = 0; i < 5; i++) {
    Serial.print("Capturing frame ");
    Serial.println(i + 1);

    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Frame capture FAILED (fb == NULL).");
      delay(500);
      continue;
    }

    Serial.print("Frame OK. Size=");
    Serial.print(fb->len);
    Serial.print(" bytes, format=");
    Serial.println((fb->format == PIXFORMAT_JPEG) ? "JPEG" : "OTHER");

    esp_camera_fb_return(fb);
    delay(500);
  }

  Serial.println("Test done. Restart or reset to re-run.");
}

void loop() {
  delay(1000);
}

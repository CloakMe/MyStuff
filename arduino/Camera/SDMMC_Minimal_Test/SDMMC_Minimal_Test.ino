/*
  SDMMC_Minimal_Test
  --------------------
  No camera involved at all - just mounts the SD card and tries to
  create, write, and read back a test file. Use this to check whether
  SD writes work at all on your board/card before troubleshooting the
  camera sketch further.

  Board: AI-Thinker ESP32-CAM
*/

#include "FS.h"
#include "SD_MMC.h"

void listDir(const char *dirname) {
  Serial.printf("Listing directory: %s\n", dirname);
  File root = SD_MMC.open(dirname);
  if (!root) {
    Serial.println("  Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("  Not a directory");
    return;
  }
  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.printf("  DIR  : %s\n", file.name());
    } else {
      Serial.printf("  FILE : %s  (%u bytes)\n", file.name(), file.size());
    }
    file = root.openNextFile();
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== SD_MMC minimal write/read test ===");

  if (!SD_MMC.begin("/sdcard", true, true)) {  // true = 1-bit mode
    Serial.println("FAIL: SD_MMC.begin() failed - card not mounting at all");
    return;
  }

  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("FAIL: No SD card detected after mount");
    return;
  }

  const char *typeStr =
    (cardType == CARD_MMC)  ? "MMC" :
    (cardType == CARD_SD)   ? "SDSC" :
    (cardType == CARD_SDHC) ? "SDHC" : "UNKNOWN";
  Serial.printf("Card mounted. Type: %s, Size: %lluMB\n", typeStr, SD_MMC.cardSize() / (1024 * 1024));

  listDir("/sdcard");

  Serial.println("--- Attempting to open test.txt for writing ---");
  File file = SD_MMC.open("/sdcard/test.txt", FILE_WRITE);
  if (!file) {
    Serial.println("FAIL: could not open /sdcard/test.txt for writing");
    Serial.println("This confirms the write failure is NOT specific to the camera sketch.");
    return;
  }

  file.println("Hello from ESP32-CAM SD_MMC test");
  file.close();
  Serial.println("OK: wrote test.txt successfully");

  Serial.println("--- Reading it back ---");
  file = SD_MMC.open("/sdcard/test.txt");
  if (!file) {
    Serial.println("FAIL: could not reopen test.txt for reading");
    return;
  }
  Serial.println("Contents:");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();

  Serial.println();
  Serial.println("=== TEST PASSED: SD card write/read works ===");
}

void loop() {
  // nothing to do
}

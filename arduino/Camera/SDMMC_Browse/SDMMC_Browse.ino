/*
  SDMMC_Browse
  --------------
  Lists every file and folder on the SD card, with sizes, and prints
  the contents of small text files directly. Useful for checking what's
  on the card without needing a phone or card reader.

  Board: AI-Thinker ESP32-CAM
*/

#include "FS.h"
#include "SD_MMC.h"

// Files smaller than this will have their contents printed too
#define MAX_TEXT_PREVIEW_BYTES 2048

void listDirRecursive(const char *dirname, int depth) {
  File root = SD_MMC.open(dirname);
  if (!root) {
    Serial.printf("Failed to open %s\n", dirname);
    return;
  }
  if (!root.isDirectory()) {
    Serial.printf("%s is not a directory\n", dirname);
    return;
  }

  File entry = root.openNextFile();
  while (entry) {
    for (int i = 0; i < depth; i++) Serial.print("  ");

    if (entry.isDirectory()) {
      Serial.printf("[DIR]  %s\n", entry.name());
      // Recurse into subdirectory
      char subPath[128];
      snprintf(subPath, sizeof(subPath), "%s/%s", dirname, entry.name());
      listDirRecursive(subPath, depth + 1);
    } else {
      Serial.printf("%-30s %8u bytes\n", entry.name(), entry.size());

      // Preview small text-ish files
      String name = String(entry.name());
      bool looksLikeText = name.endsWith(".txt") || name.endsWith(".log") || name.endsWith(".csv");
      if (looksLikeText && entry.size() <= MAX_TEXT_PREVIEW_BYTES) {
        for (int i = 0; i < depth + 1; i++) Serial.print("  ");
        Serial.println("--- content ---");
        while (entry.available()) {
          Serial.write(entry.read());
        }
        Serial.println();
        for (int i = 0; i < depth + 1; i++) Serial.print("  ");
        Serial.println("--- end ---");
      }
    }
    entry = root.openNextFile();
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== SD card browser ===");

  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("FAIL: SD card mount failed");
    return;
  }

  if (SD_MMC.cardType() == CARD_NONE) {
    Serial.println("FAIL: No SD card detected");
    return;
  }

  uint64_t totalMB = SD_MMC.cardSize() / (1024 * 1024);
  uint64_t usedMB  = SD_MMC.usedBytes() / (1024 * 1024);
  Serial.printf("Card size: %lluMB, used: %lluMB\n\n", totalMB, usedMB);

  Serial.println("--- Contents ---");
  listDirRecursive("/sdcard", 0);
  Serial.println("--- End of listing ---");
}

void loop() {
  // nothing to do
}

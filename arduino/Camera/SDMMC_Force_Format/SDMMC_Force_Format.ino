/*
  SDMMC_Force_Format
  --------------------
  Forces a real FAT32 format on the SD card using the low-level ESP-IDF
  API directly (esp_vfs_fat_sdcard_format), instead of relying on the
  Arduino SD_MMC wrapper's format_if_mount_failed flag.

  WARNING: this ERASES the card completely. Only run this once to fix
  a card that won't mount/write correctly; you don't need it for
  normal operation afterward.

  Board: AI-Thinker ESP32-CAM
*/

#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"
#include "sdmmc_cmd.h"

sdmmc_card_t *card;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== SD force-format tool ===");

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = true,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
  };

  sdmmc_host_t host = SDMMC_HOST_DEFAULT();

  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = 1;  // 1-bit mode, matches the rest of the project

  Serial.println("Mounting (will auto-format if the current FS is unreadable)...");
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      Serial.println("FAIL: could not mount filesystem, even after attempting auto-format");
    } else {
      Serial.printf("FAIL: could not initialize the card (%s)\n", esp_err_to_name(ret));
    }
    return;
  }

  Serial.println("Card mounted. Card info:");
  sdmmc_card_print_info(stdout, card);

  Serial.println();
  Serial.println("Now forcing an explicit FAT32 format regardless of mount state...");
  ret = esp_vfs_fat_sdcard_format("/sdcard", card);
  if (ret != ESP_OK) {
    Serial.printf("FAIL: force format failed (%s)\n", esp_err_to_name(ret));
    return;
  }
  Serial.println("OK: force format completed");

  Serial.println();
  Serial.println("--- Verifying: writing a test file ---");
  FILE *f = fopen("/sdcard/test.txt", "w");
  if (f == NULL) {
    Serial.println("FAIL: could not open test.txt for writing, even after format");
    return;
  }
  fprintf(f, "Hello after force format\n");
  fclose(f);
  Serial.println("OK: wrote test.txt successfully");

  Serial.println("--- Reading it back ---");
  f = fopen("/sdcard/test.txt", "r");
  if (f == NULL) {
    Serial.println("FAIL: could not reopen test.txt for reading");
    return;
  }
  char line[128];
  if (fgets(line, sizeof(line), f) != NULL) {
    Serial.printf("Contents: %s", line);
  }
  fclose(f);

  Serial.println();
  Serial.println("=== SUCCESS: card is now formatted and working ===");
}

void loop() {
  // nothing to do
}

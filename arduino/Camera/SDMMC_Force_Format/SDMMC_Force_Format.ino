/*
  SDMMC_AutoRepair
  ------------------
  Mounts the SD card and tests whether it's actually writable. If the
  write test fails, it force-formats the card (FAT32) and tests again.
  If the write test passes, nothing is touched - no unnecessary erasing.

  This also tells apart two different failure modes:
    - Mount fails to even initialize the card at all -> almost always a
      physical/wiring/power issue. Formatting can't fix this; reseat
      the card or check wiring instead.
    - Mount "succeeds" but writing still fails -> a filesystem-level
      problem. This is what force-formatting actually fixes.

  WARNING: if formatting does trigger, it ERASES the card completely.

  Board: AI-Thinker ESP32-CAM
*/

#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"
#include "sdmmc_cmd.h"

sdmmc_card_t *card = NULL;

bool testWrite() {
  FILE *f = fopen("/sdcard/write_test.tmp", "w");
  if (f == NULL) {
    return false;
  }
  bool ok = (fprintf(f, "write test\n") > 0);
  fclose(f);

  if (ok) {
    // Clean up the probe file - don't leave clutter behind
    remove("/sdcard/write_test.tmp");
  }
  return ok;
}

void printCardInfo() {
  Serial.println("Card info:");
  sdmmc_card_print_info(stdout, card);
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== SD auto-repair tool ===");

  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = true,
    .max_files = 5,
    .allocation_unit_size = 16 * 1024
  };

  sdmmc_host_t host = SDMMC_HOST_DEFAULT();

  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = 1;  // 1-bit mode

  Serial.println("Mounting SD card...");
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      Serial.println("FAIL: card responded, but no readable filesystem and auto-format also failed.");
      Serial.println("Try running the force-format tool again, or test a different card.");
    } else {
      Serial.printf("FAIL: could not initialize the card at all (%s)\n", esp_err_to_name(ret));
      Serial.println();
      Serial.println("This usually means a WIRING or PHYSICAL CONTACT issue, not a filesystem");
      Serial.println("problem - formatting will not fix it. Try reseating the card firmly,");
      Serial.println("checking the SD slot connection, or testing a different card.");
    }
    return;
  }

  Serial.println("Card mounted. Testing write access...");
  if (testWrite()) {
    Serial.println("OK: card is writable. No formatting needed.");
    printCardInfo();
    Serial.println();
    Serial.println("=== Card is healthy - safe to use as-is ===");
    return;
  }

  Serial.println("Write test FAILED despite a successful mount.");
  Serial.println("This is the 'mounts but isn't really usable' case - forcing a real reformat...");
  Serial.println();

  ret = esp_vfs_fat_sdcard_format("/sdcard", card);
  if (ret != ESP_OK) {
    Serial.printf("FAIL: force format failed (%s)\n", esp_err_to_name(ret));
    return;
  }
  Serial.println("Force format completed. Re-testing write access...");

  if (testWrite()) {
    printCardInfo();
    Serial.println();
    Serial.println("=== SUCCESS: card was reformatted and is now writable ===");
  } else {
    Serial.println();
    Serial.println("=== STILL FAILING after a full reformat ===");
    Serial.println("This points to a hardware/wiring issue rather than a filesystem one -");
    Serial.println("try reseating the card, testing a different card, or checking the SD");
    Serial.println("slot's CLK/CMD/D0 connections and pull-ups.");
  }
}

void loop() {
  // nothing to do
}

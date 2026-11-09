/*
  WiFiFileServer
  ----------------
  Connects to your WiFi and hosts a simple web page that lists the SD
  card's contents, with download links for each file. Also exposes a
  plain-text file list and a direct download endpoint, so you can pull
  dozens of files at once with a script (curl/wget loop) instead of
  clicking one at a time.

  Flash this AFTER a capture session is done (it does not run the
  camera trigger logic) - use it purely to offload files, then
  reflash your trigger sketch for the next round.

  Board: AI-Thinker ESP32-CAM

  Usage:
    1. Fill in WIFI_SSID / WIFI_PASSWORD below.
    2. Flash and open Serial Monitor - it will print the IP address
       once connected.
    3. Open http://<that-ip>/ in a browser on the same network to
       browse and click-download files.
    4. For bulk download from a terminal (same network):
         curl http://<that-ip>/list > files.txt
         while read -r name; do
           curl -O "http://<that-ip>/download?file=$name"
         done < files.txt
*/

#include "FS.h"
#include "SD_MMC.h"
#include "pan_pack.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
// ===========================
// User configuration
// ===========================

WebServer server(80);

// ---------------------------
// Helpers
// ---------------------------
String htmlEscape(const String &in) {
  String out = in;
  out.replace("&", "&amp;");
  out.replace("<", "&lt;");
  out.replace(">", "&gt;");
  return out;
}

String contentTypeFor(const String &filename) {
  String lower = filename;
  lower.toLowerCase();
  if (lower.endsWith(".jpg") || lower.endsWith(".jpeg")) return "image/jpeg";
  if (lower.endsWith(".png"))  return "image/png";
  if (lower.endsWith(".txt") || lower.endsWith(".log")) return "text/plain";
  if (lower.endsWith(".csv"))  return "text/csv";
  return "application/octet-stream";
}

// ---------------------------
// HTTP handlers
// ---------------------------
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='utf-8'>"
                "<title>ESP32-CAM SD Card</title></head><body>";
  html += "<h2>SD Card Contents</h2>";

  File root = SD_MMC.open("/sdcard");
  if (!root || !root.isDirectory()) {
    html += "<p>Failed to open SD card root directory.</p>";
  } else {
    html += "<table border='1' cellpadding='6' cellspacing='0'>";
    html += "<tr><th>File</th><th>Size (bytes)</th><th></th></tr>";

    File entry = root.openNextFile();
    while (entry) {
      if (!entry.isDirectory()) {
        String name = String(entry.name());
        String displayName = name;
        if (displayName.startsWith("/")) displayName = displayName.substring(1);

        html += "<tr><td>" + htmlEscape(displayName) + "</td>";
        html += "<td>" + String(entry.size()) + "</td>";
        html += "<td><a href='/download?file=" + displayName + "'>Download</a></td></tr>";
      }
      entry = root.openNextFile();
    }
    html += "</table>";
  }

  html += "<p><a href='/list'>Plain-text file list</a> (for scripted bulk download)</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleList() {
  String out;
  File root = SD_MMC.open("/sdcard");
  if (!root || !root.isDirectory()) {
    server.send(500, "text/plain", "Failed to open SD card root directory");
    return;
  }
  File entry = root.openNextFile();
  while (entry) {
    if (!entry.isDirectory()) {
      String name = String(entry.name());
      if (name.startsWith("/")) name = name.substring(1);
      out += name + "\n";
    }
    entry = root.openNextFile();
  }
  server.send(200, "text/plain", out);
}

void handleDownload() {
  if (!server.hasArg("file")) {
    server.send(400, "text/plain", "Missing 'file' parameter");
    return;
  }

  String filename = server.arg("file");
  String path = "/sdcard/" + filename;

  File f = SD_MMC.open(path);
  if (!f || f.isDirectory()) {
    server.send(404, "text/plain", "File not found: " + filename);
    return;
  }

  server.sendHeader("Content-Disposition", "attachment; filename=\"" + filename + "\"");
  server.streamFile(f, contentTypeFor(filename));
  f.close();
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

// ---------------------------
// Setup
// ---------------------------
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();

  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("FAIL: SD card mount failed");
    return;
  }
  if (SD_MMC.cardType() == CARD_NONE) {
    Serial.println("FAIL: No SD card detected");
    return;
  }
  Serial.println("SD card mounted.");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected. IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp32cam")) {
    Serial.println("Also reachable at http://esp32cam.local/");
  }
  Serial.println("Open that address in a browser on the same network.");

  server.on("/", handleRoot);
  server.on("/list", handleList);
  server.on("/download", handleDownload);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}

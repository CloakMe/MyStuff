#define PIR_PIN 13
void setup() { Serial.begin(115200); pinMode(PIR_PIN, INPUT_PULLDOWN); }
void loop() {
  static int last = -1;
  int v = digitalRead(PIR_PIN);
  if (v != last) { Serial.println(v ? "MOTION (HIGH)" : "idle (LOW)"); last = v; }
  delay(50);
}

// Pin definitions
#define Pin2     3//control pin - Transistor base

float ahtValue;

void setup() 
{
  Serial.begin(9600);
  Serial.print(F("Hello! Open pins\n"));

pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
digitalWrite(4, HIGH);  // Set pin 4 to HIGH 
digitalWrite(3, HIGH);  // Set pin 4 to HIGH 
digitalWrite(5, HIGH); 
digitalWrite(8, HIGH); 
digitalWrite(9, HIGH); 
Serial.print(F("Done\n"));
}
 
void loop() 
{
}

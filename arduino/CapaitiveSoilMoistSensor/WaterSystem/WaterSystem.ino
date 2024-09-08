// Pin definitions
#include <avr/wdt.h>
#include <avr/sleep.h>

#define soilWet 300  // Threshold for wet soil (adjust based on your sensor)
#define soilDry 600  // Threshold for dry soil (adjust based on your sensor)
#define sensorPin A0 // Analog pin connected to the sensor
#define powerPin 7   // Digital pin to control the power to the sensor
#define valvePin 4   // Set the solenoid valve pin as an output

#define ledPin  13

void setup()
{
  Serial.begin(9600);
  Serial.print(F("Hello! Open pins\n"));

  pinMode(powerPin, OUTPUT); // Set the power pin as an output
  digitalWrite(powerPin, LOW); // Initially turn off the sensor

  pinMode(valvePin, OUTPUT); // Set the solenoid valve pin as an output
  digitalWrite(valvePin, LOW);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.print(F("Init Done\n"));
}

void loop() {
  int moisture = getSoilMoisture();
  TryWater(moisture); //with 1 hour delay

  delay(36000000); //wait for 10 hours
  // Code to execute after waking up
  Serial.println("Woke up after 10 hours!");

  moisture = getSoilMoisture();
  TryWater(moisture); //with 1 hour delay
  delay(43200000); //wait for 10 hours
}


int getSoilMoisture()
{
  // Power on the soil moisture sensor
  digitalWrite(powerPin, HIGH);
  delay(200); // Allow time for the sensor to stabilize

  // Read the moisture level
  //int moisture = readSensor();
  int moisture = 700;
  Serial.print("Analog Output: ");
  Serial.println(moisture); // Print the moisture level
  // Power down the sensor
  digitalWrite(powerPin, LOW);
  return moisture;
}

void TryWater(int moisture)
{
  // Determine the soil status
  if (moisture < soilWet) {
    Serial.println("Status: Soil is too wet");
    delay(3600000);
  } else if (moisture >= soilWet && moisture < soilDry) {
    Serial.println("Status: Soil moisture is perfect");
    delay(3600000);
  } else {
    for (int i = 0; i < 10; i++)
    {
      waterStep();
    }
  }
}

int readSensor() {
  return analogRead(sensorPin); // Read and return the analog value from the sensor
}

void waterStep() // takes 6  minutes
{
  digitalWrite(ledPin, HIGH);
  Serial.println("Status: watering procedure: 1 min water; 5 min sleep to cool the solenoid!");
  digitalWrite(valvePin, HIGH); // turn on the solenoid valve
  delay(60000); // 1 minute in milliseconds
  digitalWrite(valvePin, LOW); // turn oFF the solenoid valve
  digitalWrite(ledPin, LOW);
  for (int i = 0; i < 30; i++)
  {
    delay(5000); // 5 sec
    digitalWrite(ledPin, HIGH);
    delay(5000); // 5 sec
    digitalWrite(ledPin, LOW);
  }
}

int lowPowerSleep()
{
  // Set up the watchdog timer for 8 seconds
  wdt_enable(WDTO_8S);
  // Sleep for 12 hours (43,200,000 milliseconds)
  for (unsigned long i = 0; i < 5; i++) { // 3600 cycles of ~8 seconds  --- 3600

    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode to power down
    sleep_mode(); // Enter sleep mode

    // The microcontroller will wake up here after the watchdog timer expires
    // Disable the watchdog timer
    wdt_disable();
  }
}

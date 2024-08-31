// Pin definitions
#include <avr/wdt.h>

#define soilWet 300  // Threshold for wet soil (adjust based on your sensor)
#define soilDry 600  // Threshold for dry soil (adjust based on your sensor)
#define sensorPin A0 // Analog pin connected to the sensor
#define powerPin 7   // Digital pin to control the power to the sensor
#define valvePin 4   // Set the solenoid valve pin as an output

void setup() {
    Serial.begin(9600); // Initialize serial communication
}

void setup() 
{
  Serial.begin(9600);
  Serial.print(F("Hello! Open pins\n"));
  
  pinMode(powerPin, OUTPUT); // Set the power pin as an output
  digitalWrite(powerPin, LOW); // Initially turn off the sensor
  
  pinMode(powerPin, OUTPUT); // Set the solenoid valve pin as an output
  
  Serial.print(F("Init Done\n"));
}
 
void loop() {
    // Power on the soil moisture sensor
    digitalWrite(powerPin, HIGH);
    delay(500); // Allow time for the sensor to stabilize

    // Read the moisture level
    int moisture = readSensor();
    Serial.print("Analog Output: ");
    Serial.println(moisture); // Print the moisture level

    // Determine the soil status
    if (moisture < soilWet) {
        Serial.println("Status: Soil is too wet");
    } else if (moisture >= soilWet && moisture < soilDry) {
        Serial.println("Status: Soil moisture is perfect");
    } else {
        Serial.println("Status: Soil is too dry - time to water!");
        digitalWrite(valvePin, HIGH); // turn on the solenoid valve
        delay(1000 * 60 * 5); // 5 minutes in milliseconds
        digitalWrite(valvePin, LOW); // turn oFF the solenoid valve
    }

    // Power down the sensor
    digitalWrite(powerPin, LOW);

    // Sleep for 12 hours (43,200,000 milliseconds)
    for (unsigned long i = 0; i < 3600; i++) { // 3600 cycles of ~8 seconds
        // Set up the watchdog timer for 8 seconds
        wdt_enable(WDTO_8S);
        // Enter sleep mode
        asm volatile ("sleep");
        // Disable watchdog timer
        wdt_disable();
    }

    // Code to execute after waking up
    Serial.println("Woke up after 12 hours!");
    delay(1000); // Delay for a while to observe the message
}

int readSensor() {
    return analogRead(sensorPin); // Read and return the analog value from the sensor
}

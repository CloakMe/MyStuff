#include <LowPower.h>

int VALVE_PIN = 7;
int THOUSAND_MS = 3000;

void setup() 
{
  pinMode(VALVE_PIN, OUTPUT);
	pinMode(2, INPUT_PULLUP); // wake pin (INT0)
  
  // pinMode(13, OUTPUT); // DEBUG
  SleepLowPower(6 * 60); //6 hours
  // blink(); // DEBUG
}
	
void loop()
{  
	// do work  
  waterStep();

  SleepLowPower(24 * 60); //
	// resume here after wake

  // blink(); // DEBUG
}


void SleepLowPower(int minutes)
{
  // bool flag = minutes % 2 == 1;
  
  int num_cycles = (int)(7.3 * minutes);
  for(int i=0; i<num_cycles; i++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); // sleep for 8 s using WDT  
  }

  // LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF); // sleep for 4 s using WDT 
}

void waterStep() // takes 20 sec for watering 900ml of water with water pump
{
  digitalWrite(VALVE_PIN, HIGH); // turn on the solenoid valve
  delay(40000); // 40 sec in milliseconds
  digitalWrite(VALVE_PIN, LOW); // turn oFF the solenoid valve
}

void blink() // DEBUG
{
  for(int i=0; i<60; i++)
  {
  digitalWrite(13, HIGH);  
  delay(500);  
  digitalWrite(13, LOW);  
  delay(500);
  }
}

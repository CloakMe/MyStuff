#include <SoftwareSerial.h>
SoftwareSerial SIM900A(7,8); // RX | TX
// Connect the SIM900A TX to Arduino pin 2 RX. 
// Connect the SIM900A RX to Arduino pin 3 TX. 
char c = ' ';
void setup() 
{
// start th serial communication with the host computer
Serial.begin(9600);
while(!Serial);
Serial.println("Arduino with SIM900A is ready");

// start communication with the SIM900A in 9600
SIM900A.begin(115200); 
Serial.println("SIM900A started at 115200");
delay(1000);
Serial.println("Setup Complete! SIM900A is Ready!");
delay(1000);
}

void loop()
{
   if (SIM900A.available())
       Serial.write(SIM900A.read());
   if (Serial.available())
       SIM900A.write(Serial.read());

// Keep reading from SIM800 and send to Arduino Serial Monitor
//if (SIM900A.available())
//{ c = SIM900A.read();
//Serial.write(c);}
//
//// Keep reading from Arduino Serial Monitor and send to SIM900A
//if (Serial.available())
//{ c = Serial.read();
//SIM900A.write(c); 
//}

}

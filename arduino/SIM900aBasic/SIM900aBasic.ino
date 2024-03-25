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
    SIM900A.begin(9600);
    Serial.println("SIM900A started at 9600");
    delay(1000);
    Serial.println("Setup Complete! SIM900A is Ready!");
}
int ok = 0;
bool CheckRing(char r)
{
    int current = ok;
    switch(r)
    {
        case 'R':
        {
            current = 1;break;
        }
        case 'I':
        {
            current = 2;break;
        }
        case 'N':
        {
            current = 3;break;
        }
        case 'G':
        {
            current = 4;break;
        }
    }
    
    if(current != ok+1)
    {
        ok = 0;
        return false;
    }
    else
        ok = current;

    if(ok == current && r == 'G')
        return true;

    return false;
}

void loop()
{
    // Keep reading from SIM900A and send to Arduino Serial Monitor
    if (SIM900A.available())
    { 
        c = SIM900A.read();
        if(c != -16)
        {
            //int yo = c;
            Serial.write(c);
            //Serial.print(yo);
            if(CheckRing(c))
            {
                Serial.println("-----------ringing---------");
            }
        }
    }

    // Keep reading from Arduino Serial Monitor and send to SIM900A
    if (Serial.available())
    { 
        c = Serial.read();
        SIM900A.write(c); 
    }
}

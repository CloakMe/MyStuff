#include <SoftwareSerial.h> //sim900a module

//display module
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//end display module


SoftwareSerial SIM900A(7,8); // RX | TX

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() 
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        //Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.display();
    delay(2000); // Pause for 2 seconds
    // start th serial communication with the host computer
    //Serial.begin(9600);
    //while(!Serial);
    //Serial.println("Serial begin at 9600");

    // start communication with the SIM900A in 9600
    SIM900A.begin(115200);
    //Serial.println("SIM900A begin at 115200");
    display.clearDisplay();
    
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    //display.setCursor(10, 0);
    display.println(F("SIM900A at 115200"));
    display.display();     
    delay(1000);
}

char c;
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
            //Serial.write(c);
            //Serial.print(yo);
            display.write(c);
            CheckClearScreen();
            if(CheckRing(c))
            {
                //Serial.println("--ringing--");
                display.println(F("--ringing--"));
                CheckClearScreen();
                SIM900A.println("ATA");
            }
        }
    }

    // Keep reading from Arduino Serial Monitor and send to SIM900A
    //if (Serial.available())
    //{ 
    //    c = Serial.read();
    //    SIM900A.write(c);
    //}
}

void CheckClearScreen()
{
    int16_t ypos = display.getCursorY();
    if(ypos >= SCREEN_HEIGHT)
    {
        delay(1000);
        display.clearDisplay();
        display.setCursor(0, 0);
    }
}

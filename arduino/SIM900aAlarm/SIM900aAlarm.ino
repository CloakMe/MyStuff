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
bool displayInit = false;
bool displaySerial = false;
void setup()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        //Serial.println(F("SSD1306 allocation failed"));
        //for(;;); // Don't proceed, loop forever
        displayInit = false;
    }
    else
        displayInit = true;
    
    if(displayInit)
    {
        //display.setRotation(2);
        display.display();
    }
    delay(2000); // Pause for 2 seconds
    // start th serial communication with the host computer
    if(displaySerial)
    {
        Serial.begin(9600);
        while(!Serial);
        Serial.println("Serial begin at 9600");
    }
    // start communication with the SIM900A in 9600
    SIM900A.begin(115200);
    if(displaySerial)
        Serial.println("SIM900A begin at 115200");
    if(displayInit)
    {
        display.clearDisplay();
        display.setTextSize(1); // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        //display.setCursor(10, 0);
        DisplayPrint("SIM900A at 115200");
    }

    delay(2000);
    SIM900A.println("AT");
}

char c = '0';
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

char lastChar = '\a';
bool CheckOk(char r)
{
    switch(r)
    {
        case 'O':
        {
            lastChar = 'O';
            return false;
        }
        case 'K':
        {
            if(lastChar == 'O')
                return true;
            else
                lastChar = '\a';
        }
    }
    return false;
}

unsigned long working = 0;
unsigned long startMillis = millis(); // Start of sample window
void loop()
{
    // Keep reading from SIM900A and send to Arduino Serial Monitor
    if (SIM900A.available())
    {
        c = SIM900A.read();
        if(c != -16)
        {
            //int yo = c;
            if(displaySerial)
                Serial.write(c);
            //Serial.print(yo);
            if(false)
            {
                display.write(c);
                display.display();
                CheckClearScreen();              
            }
            if(CheckOk(c))
            {
                if(displaySerial)
                    Serial.println("--ringing--");
                if(displayInit)
                {
                    DisplayWrite("ok");
                }
            }
            if(CheckRing(c))
            {
                if(displaySerial)
                    Serial.println("--ringing--");
                if(displayInit)
                {
                    DisplayPrint("--ringing--");
                }
                SIM900A.println("ATA");
            }
        }
        working++;
    }
    else
    {
        if(millis() - startMillis > 15000)
        {
          String buffer("SIM avail: ");
          buffer += working;
          //if(displayInit)
          //    DisplayPrint(buffer.c_str());
          if(displaySerial)
              Serial.println(buffer.c_str());
          startMillis = millis();
          working = 0;
          SIM900A.println("AT");
        }
    }

    // Keep reading from Arduino Serial Monitor and send to SIM900A
    if(displaySerial)
        if (Serial.available())
        { 
            c = Serial.read();
            SIM900A.write(c);
        }
}

void CheckClearScreen()
{
    int16_t xpos = display.getCursorX();
    if(xpos >= SCREEN_WIDTH)
    {
        display.setCursor(0, display.getCursorY()+8);
    }
    int16_t ypos = display.getCursorY();
    if(ypos >= SCREEN_HEIGHT)
    {
        delay(1000);
        display.clearDisplay();
        display.setCursor(0, 0);
    }
}

void DisplayPrint(const char * message)
{
    display.println(message);
    display.display();
    CheckClearScreen();
}

void DisplayWrite(const char * message)
{
    display.write(message);
    display.display();
    CheckClearScreen();
}

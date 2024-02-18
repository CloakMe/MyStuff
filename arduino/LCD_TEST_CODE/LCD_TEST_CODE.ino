//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////LIBRARY DEFINATION///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include <Adafruit_GFX.h>  
#include <Adafruit_Sensor.h>  
#include <Adafruit_ST7735.h> 
#include <Wire.h>
#include <SPI.h>
 
#define TFT_CS    10
#define TFT_RST   8  
#define TFT_DC    9 
#define TFT_SCLK 13   
#define TFT_MOSI 11

//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////LIBRARY DEFINATION END////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//.............................................................................//
////////////////////////VARIABLE DECLARATION ////////////////////////////////////
//.............................................................................//
byte count =10; bool t =0;
//.............................................................................//
////////////////////////VARIABLE DECLARATION END ////////////////////////////////
//.............................................................................//

void setup(void) 
{
 //........................LCD INITIALIZATION.........................................//
  tft.initR(INITR_BLACKTAB);  
  tft.fillScreen(ST7735_BLACK); 

  tft.drawRoundRect(3, 5, 122, 150,5, ST7735_BLUE);
  tft.setCursor(30, 20);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(2);
  tft.println("SYSTEM");
  tft.setCursor(30, 45);
  tft.println("STARTS");
  tft.setCursor(50, 70);
  tft.println("IN");

  tft.drawRect(8 , 125, 112, 25,ST7735_BLUE);
  tft.fillRect(11, 128, 8, 19, ST7735_RED);

}

void display()
{
  tft.drawRoundRect(40, 90, 40,25,5, ST7735_BLACK);
    tft.fillRoundRect(40, 90, 40,25,5, ST7735_BLACK);
    tft.setCursor(55, 95);
    tft.println(count);

    if ( count == 9)
    {
      tft.fillRect(22, 128, 8, 19,ST7735_RED);
    }
    else if (count == 8)
    {
      tft.fillRect(33, 128, 8, 19,ST7735_YELLOW);
    }
    else if (count == 7)
    {
      tft.fillRect(44, 128, 8, 19,ST7735_YELLOW);
    }
    else if (count == 6)
    {
      tft.fillRect(55, 128, 8, 19,ST7735_BLUE);
    }
    else if (count == 5)
    {
       tft.fillRect(66, 128, 8, 19,ST7735_BLUE);
    }
    else if (count == 4)
    {
      tft.fillRect(77, 128, 8, 19,ST7735_BLUE);
    }
    else if (count == 3)
    {
       tft.fillRect(88, 128, 8, 19,ST7735_BLUE);
    }
    else if (count == 2)
    {
      tft.fillRect(98, 128, 8, 19,ST7735_GREEN);
    }
    else if (count == 1)
    {
      tft.fillRect(108, 128, 8, 19,ST7735_GREEN);
    }
}


void loop() 
{
  if (count > 0)
  {
    count = count - 1;
    delay (1000);
    display();

  }
  else
  {
   
    if (t == 0)
    {
      tft.fillScreen(ST7735_BLACK);

      tft.drawCircle(6, 6 ,10, ST7735_YELLOW);
      tft.fillCircle(6, 6 ,10, ST7735_YELLOW);

      tft.drawLine(5, 5 ,10,30, ST7735_YELLOW);
      tft.drawLine(5, 5 ,23,23, ST7735_YELLOW);
      tft.drawLine(5, 5 ,30,10, ST7735_YELLOW);
      
      tft.drawLine(3, 3 ,3,25, ST7735_YELLOW);
      tft.drawLine(3, 3 ,25,3, ST7735_YELLOW);
      
      tft.drawLine(30, 30 ,110,30, ST7735_WHITE);
      tft.drawLine(27, 27 ,116,27, ST7735_WHITE);
      
      tft.drawLine(10, 70 ,90,70, ST7735_WHITE);
      tft.drawLine(4, 73 ,93,73, ST7735_WHITE);
      
      tft.drawLine(30, 30 ,10,70, ST7735_WHITE);
      tft.drawLine(27, 27 ,4,73, ST7735_WHITE);
      
      tft.drawLine(110, 30 ,90,70, ST7735_WHITE);
      tft.drawLine(116, 27 ,93,73, ST7735_WHITE);

      
      
      tft.drawLine(20, 50 ,100,50, ST7735_WHITE);
      tft.drawLine(57, 30 ,37,70, ST7735_WHITE);
      tft.drawLine(84, 30 ,64,70, ST7735_WHITE);

      tft.drawCircle(38, 40 ,4, ST7735_WHITE);
      tft.drawCircle(65, 40 ,4, ST7735_WHITE);
      tft.drawCircle(92, 40 ,4, ST7735_WHITE);

      tft.drawCircle(30, 60 ,4, ST7735_WHITE);
      tft.drawCircle(57, 60 ,4, ST7735_WHITE);
      tft.drawCircle(84, 60 ,4, ST7735_WHITE);

      tft.setTextSize(2);
      tft.setCursor(35, 85);
      tft.println("SOLAR");
      tft.setCursor(35, 110);
      tft.println("PANEL");
      tft.setCursor(5, 135);
      tft.println("MONITORING");
      
      
      
      
      t=1;
    }
    else
    {
      
    }
    
  }
  
}
  

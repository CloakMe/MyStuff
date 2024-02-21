#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
 
// Pin definitions
#define TFT_CLK     10//sck
#define TFT_MOSI    9 //sda
#define TFT_RST     7 //reset
#define TFT_DC      6 //RS (DC)
#define TFT_CS      5 //CS
#define TFT_MISO    0

// Create an instance of the Adafruit ST7735 library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);
 
void setup() 
{
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test\n"));
  
  // Initialize the display
  tft.initR(INITR_BLACKTAB); // Use this initialization for a black tab display
  Serial.println(F("Initialized"));
  
  uint16_t time = millis();
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  time = millis() - time;
  Serial.println(time, DEC);
  delay(500);
  
  //tft.fillScreen(0x0000); // Fill the screen with black ST77XX_BLACK
  // Set text color and size
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.setCursor(3, 3);
  tft.println("Hello,");
  tft.setCursor(3, 20);
  // Display a welcome message
  tft.println("ST7735!");
  delay(5000);
  // Draw a rectangle
  tft.fillRect(40, 50, 80, 50, ST7735_RED);
}
 
void loop() {
  //tft.invertDisplay(true);
  //delay(2500);
  //tft.invertDisplay(false);
  //delay(2500);
}

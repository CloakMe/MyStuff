//#include <Adafruit_GFX.h>
//#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <TFT.h>
// Pin definitions
#define TFT_PIN3_CLK     13//sck 1mA  -> 5000 Ohm
#define TFT_PIN4_MOSI    11 //sda (1-2.5mA) -> 5000 Ohm
#define TFT_PIN5_RST     8 //reset (5.5-8mA)
#define TFT_PIN6_DC      9 //RS (DC) (5-7mA) -> 715-1000 Ohm
#define TFT_PIN7_CS      10 //CS 0.006A (6mA) -> 833 Ohm
//#define TFT_PIN5_RST     7 //reset (5.5-8mA)
//#define TFT_PIN6_DC      6 //RS (DC) (5-7mA) -> 715-1000 Ohm
//#define TFT_PIN7_CS      5 //CS 0.006A (6mA) -> 833 Ohm
#define TFT_MISO    0

// Create an instance of the Adafruit ST7735 library
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN7_CS, TFT_PIN6_DC, TFT_PIN4_MOSI, TFT_PIN3_CLK, TFT_PIN5_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN7_CS, TFT_PIN6_DC, TFT_PIN5_RST);
TFT tft = TFT(TFT_PIN7_CS, TFT_PIN6_DC, TFT_PIN5_RST);
//TFT(CS, DC, MOSI, SCLK, RESET);
#define ST7735_BLACK   0x0000
#define ST7735_GRAY    0x8410
#define ST7735_WHITE   0xFFFF
#define ST7735_RED     0xF800
#define ST7735_ORANGE  0xFA60
#define ST7735_YELLOW  0xFFE0  
#define ST7735_LIME    0x07FF
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_AQUA    0x04FF
#define ST7735_BLUE    0x001F
#define ST7735_MAGENTA 0xF81F
#define ST7735_PINK    0xF8FF

void setup() 
{
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test\n"));
  
  // Initialize the display
  tft.initR(INITR_BLACKTAB); // Use this initialization for a black tab display
  //Serial.println(F("Initialized"));
  
  uint16_t time = millis();
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK); //ST77XX_BLACK

  time = millis() - time;
  //Serial.println(time, DEC);
  delay(500);
  
  //tft.fillScreen(ST7735_BLACK); // Fill the screen with black ST77XX_BLACK
  // Set text color and size
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.setCursor(3, 3);
  tft.println("Hello,");
  tft.setCursor(3, 20);
  // Display a welcome message
  tft.println("ST7735!");
  delay(1000);
  // Draw a rectangle
  tft.fillRect(40, 50, 80, 50, ST7735_RED);
  delay(1000);
  Serial.println("remove CLK");
  //digitalWrite(TFT_PIN3_CLK, LOW);
  digitalWrite(TFT_PIN3_CLK, LOW);
  
  delay(10000);
  Serial.println("remove RST DC");
  //digitalWrite(TFT_PIN5_RST, LOW);
  digitalWrite(TFT_PIN6_DC, LOW);
  digitalWrite(TFT_PIN7_CS, LOW);
}
 
void loop() {
  //tft.invertDisplay(true);
  //delay(2500);
  //tft.invertDisplay(false);
  //delay(2500);
}

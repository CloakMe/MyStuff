#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <AHTxx.h>
// Pin definitions
#define TFT_PIN3_CLK     12//sck 1mA  -> 5000 Ohm
#define TFT_PIN4_MOSI    11 //sda (1-2.5mA) -> 5000 Ohm
#define TFT_PIN5_RST     10 //reset (5.5-8mA)
#define TFT_PIN6_DC      9 //RS (DC) (5-7mA) -> 715-1000 Ohm
#define TFT_PIN7_CS      8 //CS 0.006A (6mA) -> 833 Ohm
#define TFT_MISO    0

// Create an instance of the Adafruit ST7735 library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN7_CS, TFT_PIN6_DC, TFT_PIN4_MOSI, TFT_PIN3_CLK, TFT_PIN5_RST);
AHTxx aht10(AHTXX_ADDRESS_X38, AHT1x_SENSOR); //sensor address, sensor type
float ahtValue;
int i = 70;
int cur_pos = 20;
void setup() 
{
  Serial.begin(9600);
  Serial.print(F("Hello! TFT initializing\n"));
  
  // Initialize the display
  tft.initR(INITR_BLACKTAB); // Use this initialization for a black tab display
  //Serial.println(F("Initialized"));
  
  uint16_t time = millis();
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK); //ST77XX_BLACK

  time = millis() - time;
  //Serial.println(time, DEC);
  delay(500);
  
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(2);
  tft.setCursor(3, 3);
  tft.println("--Hello <3--");
  
  tft.setCursor(3, 23);
  // Display a welcome message
  tft.println("TFT started!");
  delay(1000);
  // Draw a rectangle
  Serial.println("AHT15 initializing!\n");
  tft.setCursor(3, 43);
  tft.println("-AHT15 init-");  
  while (aht10.begin() != true) //for ESP-01 use aht10.begin(0, 2);
  {
    Serial.println(F("AHT15 not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free

    delay(5000);
  }

  Serial.println(F("AHT15 OK!"));
  tft.setCursor(3, 63);
  
  tft.println("--AHT15 OK--");
  delay(4000);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(1);
  tft.setCursor(2, 1);
  tft.println(F("65"));
  
  tft.setCursor(4, 41);
  tft.println(F("55"));
  
  tft.setCursor(4, 81);
  tft.println(F("45"));  
  
  tft.setCursor(4, 121);
  tft.println(F("35"));

  tft.drawRect(20, 4, 139, 120, ST7735_RED);
  tft.setTextSize(2);
}
 
void loop() 
{
  if(i==0)
  {
    delay(3000);
    return;
  }
  ahtValue = aht10.readTemperature(); //read another 6-bytes via I2C, takes 80 milliseconds
  tft.fillRect(95, 6, 58, 15, ST7735_BLACK);
  tft.setCursor(95, 6);
  tft.print(ahtValue);
  delay(1500);
  ahtValue = aht10.readHumidity(); //read another 6-bytes via I2C, takes 80 milliseconds
  tft.fillRect(22, 6, 58, 15, ST7735_BLACK);
  tft.setCursor(22, 6);
  tft.print(ahtValue);

  if (ahtValue != AHTXX_ERROR) //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    if( ahtValue <= 35 )
      ahtValue = 35;
    if( ahtValue >= 65 )
      ahtValue = 65;
    float newAhtValue = (ahtValue - 35) * 4;
    //Serial.println(F("newAhtValue "));
    //Serial.println(newAhtValue);
    tft.drawRect(cur_pos, (int)(124.0 - newAhtValue), 2, (int)newAhtValue, ST7735_GREEN);
  }
  
  tft.drawRect(20, 21, 139, 1, ST7735_RED);
  tft.drawRect(20, 41, 139, 1, ST7735_RED);
  tft.drawRect(20, 61, 139, 1, ST7735_RED);
  tft.drawRect(20, 81, 139, 1, ST7735_RED);
  tft.drawRect(20, 101, 139, 1, ST7735_RED);
  //measurement with high frequency leads to heating of the sensor, see NOTE
  delay(462000); //7.7 min
  //delay(10000); //for testing
  --i;
  cur_pos = cur_pos+2;
}

void printStatus()
{
  tft.setCursor(3, 103);
  switch (aht10.getStatus())
  {
    case AHTXX_NO_ERROR:
      tft.println(F("no error"));
      break;

    case AHTXX_BUSY_ERROR:
      tft.println(F("busy, incr poll time"));
      break;

    case AHTXX_ACK_ERROR:
      tft.println(F("no return ACK")); //, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)));
      break;

    case AHTXX_DATA_ERROR:
      tft.println(F("rcvd data smaller"));// than expected, not connected, broken, long wires (reduce speed), bus locked by slave (increase stretch limit)"));
      break;

    default:
      tft.println(F("unknown status"));    
      break;
  }
}

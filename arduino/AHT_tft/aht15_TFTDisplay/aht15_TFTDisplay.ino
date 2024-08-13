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
  tft.setCursor(3, 3);
  tft.println(F("Read temp/hum"));
}
 
void loop() 
{
  ahtValue = aht10.readTemperature(); //read 6-bytes via I2C, takes 80 milliseconds
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(3, 33);  
  tft.setTextSize(3);
  tft.print(F("T:"));  
  if (ahtValue != AHTXX_ERROR) //AHTXX_ERROR = 255, library returns 255 if error occurs
  {    
    Serial.print("T = ");
    Serial.print(ahtValue);
    Serial.println("C");
    tft.print(ahtValue);
    tft.println(F("C"));
  }
  else
  {
    tft.setTextSize(2);
    printStatus(); //print temperature command status

    if   (aht10.softReset() == true) tft.println(F("reset success")); //as the last chance to make it alive
    else                             tft.println(F("reset failed"));
  }

  delay(2000); //measurement with high frequency leads to heating of the sensor, see NOTE

  ahtValue = aht10.readHumidity(); //read another 6-bytes via I2C, takes 80 milliseconds
  tft.setCursor(3, 73);
  
  tft.setTextSize(3);
  tft.print(F("H:"));
  
  if (ahtValue != AHTXX_ERROR) //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    Serial.print("H = ");
    Serial.print(ahtValue);
    Serial.println("%");
    tft.print(ahtValue);
    tft.println(F("%"));
  }
  else
  {
    tft.setTextSize(2);
    printStatus(); //print humidity command status
  }

  delay(60000); //measurement with high frequency leads to heating of the sensor, see NOTE
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

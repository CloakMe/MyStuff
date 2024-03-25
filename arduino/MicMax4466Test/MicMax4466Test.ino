const int sampleWindow = 5000;  // Sample window width in mS (50 mS = 20Hz, 10 mS = 100Hz)
int const AMP_PIN = A0;       // Preamp output pin connected to A0
unsigned int sample;

void setup()
{
  Serial.begin(9600);
}

void loop00()
{
  Serial.println("----------------------------");
  unsigned long startMillis = millis(); // Start of sample window

  // collect data for 10000 mS
  while (millis() - startMillis < sampleWindow)
  {
    Serial.println(analogRead(AMP_PIN));
  }
  Serial.println("----------------------------");
}

void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS and then plot data
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(AMP_PIN);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  Serial.println( (signalMin* 5.0)/1024 );
  Serial.println( (signalMax* 5.0)/1024 );
  //double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  //Serial.println(volts);
}

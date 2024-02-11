int OK_BUTTON_PIN = 7;
int RED_DIAL_BUTTON_PIN = 8;
int POWER_ON_OFF_PIN = 2;
int FOUR_BUTTON_PIN = 10;
int FIVE_BUTTON_PIN = 11;
int SIX_BUTTON_PIN = 12;

int KEY_PRESS_TIME_MS = 120;
int LONG_KEY_PRESS_TIME_MS = 650;
int THOUSAND_MS = 1000;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(OK_BUTTON_PIN, OUTPUT);
  pinMode(RED_DIAL_BUTTON_PIN, OUTPUT);
  pinMode(POWER_ON_OFF_PIN, OUTPUT);
  pinMode(FOUR_BUTTON_PIN, OUTPUT);
  pinMode(FIVE_BUTTON_PIN, OUTPUT);
  pinMode(SIX_BUTTON_PIN, OUTPUT);  
  
  pinMode(A4, INPUT);

  Serial.begin(9600);
  Serial.print(F("HI\n"));
}

void loop() {
  int x = analogRead(A4);
  Serial.print ( "Analog value : ");
  Serial.println (x);
  if (x > 200)
  {
    Signal();
  }
  delay(THOUSAND_MS);
}

void Signal()
{
  Serial.print(F("Signal\n"));
  digitalWrite(POWER_ON_OFF_PIN, HIGH); //turn on power supply for phone
  delay(2 * THOUSAND_MS);
  Serial.print(F("Turn on phone\n"));
  digitalWrite(RED_DIAL_BUTTON_PIN, HIGH);
  delay(600);  // red button - turn on
  digitalWrite(RED_DIAL_BUTTON_PIN, LOW);
  
  delay(15 * THOUSAND_MS);
  digitalWrite(OK_BUTTON_PIN, HIGH);
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(OK_BUTTON_PIN, LOW);
  
  delay(3*THOUSAND_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, HIGH); // red
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, LOW);

  //===================
  Serial.print(F("Make call on number 4\n"));
  delay(3* THOUSAND_MS);
  digitalWrite(FOUR_BUTTON_PIN, HIGH); //make call on number 4
  delay(LONG_KEY_PRESS_TIME_MS);
  digitalWrite(FOUR_BUTTON_PIN, LOW);
  delay(30 * THOUSAND_MS);

  Serial.print(F("Stop calling on number 4\n"));
  digitalWrite(OK_BUTTON_PIN, HIGH); //turn screen on
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(OK_BUTTON_PIN, LOW);
  delay(THOUSAND_MS);
  
  digitalWrite(RED_DIAL_BUTTON_PIN, HIGH);  //red 
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, LOW);


  //===================
  delay(4 * THOUSAND_MS);
  Serial.print(F("Make call on number 5\n"));
  digitalWrite(FIVE_BUTTON_PIN, HIGH); //make call on number 5 FIVE_BUTTON_PIN
  delay(LONG_KEY_PRESS_TIME_MS);
  digitalWrite(FIVE_BUTTON_PIN, LOW);  //FIVE_BUTTON_PIN
  delay(25 * THOUSAND_MS);

  Serial.print(F("Stop calling on number 5\n"));
  digitalWrite(OK_BUTTON_PIN, HIGH); //turn screen on
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(OK_BUTTON_PIN, LOW);
  delay(THOUSAND_MS);
  
  digitalWrite(RED_DIAL_BUTTON_PIN, HIGH); 
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, LOW);

  
    //===================
  delay(4 * THOUSAND_MS);
  Serial.print(F("Make call on number 6\n"));
  digitalWrite(SIX_BUTTON_PIN, HIGH); //make call on number 6 SIX_BUTTON_PIN
  delay(LONG_KEY_PRESS_TIME_MS);
  digitalWrite(SIX_BUTTON_PIN, LOW);
  delay(25 * THOUSAND_MS); //wait for answer 30*60000

  Serial.print(F("Stop calling on number 6\n"));
  digitalWrite(OK_BUTTON_PIN, HIGH); //turn screen on
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(OK_BUTTON_PIN, LOW);
  delay(THOUSAND_MS);
  
  digitalWrite(RED_DIAL_BUTTON_PIN, HIGH);  //red 
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, LOW);

  Serial.print(F("5 sec delay before shut down\n"));
  delay(5 * THOUSAND_MS); //5 sec delay before shut down

  Serial.print(F("Shut down phone\n"));
  digitalWrite(RED_DIAL_BUTTON_PIN, HIGH);  //red 
  delay(KEY_PRESS_TIME_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, LOW);
  
  delay(THOUSAND_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, HIGH); //red long - turn off phone
  delay(LONG_KEY_PRESS_TIME_MS);
  digitalWrite(RED_DIAL_BUTTON_PIN, LOW);
  
  delay(THOUSAND_MS);
  
  digitalWrite(POWER_ON_OFF_PIN, LOW);    //cut down power supply - Sziklai switch
}

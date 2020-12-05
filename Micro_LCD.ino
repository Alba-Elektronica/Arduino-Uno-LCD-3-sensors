// Alba Elektronica @ 2020

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define sensorPower2 6

// LCD pinout
// A5  SCL, A4  SDA, 5V VCC, GND  GND
// KY-037 pinout
// D0  9, Vcc  6,  GND  14 (GND), A0  A0  

int sensorPin = A0; // select the input pin for the potentiometer
int ledPin = 9; // select the pin for the LED
int sensorValue = 100; // variable to store the value coming from the sensor

void setup(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  Serial.begin(9600); 
  pinMode (ledPin, OUTPUT);
  pinMode(sensorPower2, OUTPUT);
  digitalWrite(sensorPower2, LOW);
}

void loop(){
  sensorValue = analogRead (sensorPin);
  //sensorValue = 120 sensorValue;
  Serial.println(sensorValue * 120.0);

  digitalWrite (ledPin, HIGH);
  
  delay (100);
  digitalWrite (ledPin, LOW);
  delay (sensorValue);
  
  lcd.setCursor(0,0);
  lcd.print("Sensor val: ");
  lcd.print(sensorValue);

  digitalWrite(sensorPower2, HIGH);
  delay(100);
  int val = analogRead(sensorPin);
  //int val = digitalRead(sensorPin);
  digitalWrite(sensorPower2, LOW);

delay(1000);
}

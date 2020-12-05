// Alba Elektronica @ 2020

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
// sensorRain -->  1024 maxim, 0 minim

// LCD pinout
// A5  SCL, A4  SDA, 5V VCC, GND  GND
// MH-RD pinout
// Vcc  7,  GND  14 (GND), D0  8, A0  A0  

#define sensorPower 7
//#define sensorPin 8

void setup(){
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}

void loop()
{
  digitalWrite(sensorPower, HIGH);
  delay(100);
  int val = analogRead(A0);
  //int val = digitalRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  
  Serial.print("Digital: ");
  Serial.println(val);
  
  lcd.setCursor(0,0); 
  lcd.print("Rain: ");
  if (val > 800) {
    lcd.print("NO");
  } else if(val > 400){
    lcd.print("Some drops");
  } else {
    lcd.print("Yes");
  }

  lcd.setCursor(0,1);
  lcd.print("Coverage: ");
  lcd.print((1024-val)/1024.0);
  //lcd.setCursor(0,1);
  delay(1000);
}

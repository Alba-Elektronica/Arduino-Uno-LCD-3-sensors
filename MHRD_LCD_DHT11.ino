// Alba Elektronica @ 2020
// A combination between two experiments: the rain sensor and the humidity sensors. 
// Results are displaied on an LCD and serial monitor. 
//
//
// LCD pinout
// A5  SCL, A4  SDA, 5V VCC, GND  GND
//
// MH-RD pinout
// sensorRain -->  1024 maxim, 0 minim
// Vcc  7,  GND  14 (GND), D0  8, A0  A0  
//
// KY-015 pinout
// S  2,  +  3.3V,  -  GND 

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define DHTTYPE DHT11   // DHT 11

#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

#define sensorPower 7

void setup(){
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  dht.begin();
  
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  digitalWrite(sensorPower, HIGH);
  delay(100);
  int val = analogRead(A0);
  //int val = digitalRead(sensorPin);
  digitalWrite(sensorPower, LOW);

  Serial.print("Rain ");
  if (val > 800)
    Serial.print("Dry");
    else if (val > 400)
    Serial.print("Some drops");
    else 
    Serial.print("Yes");
    
  Serial.print("Rain coverage: ");
  Serial.println((1024 - val) / 1024.0);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);

  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");


  lcd.setCursor(0,1);
  lcd.print("Rain Coverage: ");
  lcd.print((1024-val)/1024.0);
  //lcd.setCursor(0,1);
  delay(10000);
}

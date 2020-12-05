// Alba Elektronica @ 2020
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define DHTTYPE DHT11   // DHT 11

#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// LCD pinout
// A5  SCL, A4  SDA, 5V VCC, GND  GND
// KY-015 pinout
// S  2,  +  3.3V,  -  GND 

void setup(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
  Serial.begin(9600);
  
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

  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Humidity max: ");
  lcd.print(h);
  lcd.print("%");

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);

  // Set delay between sensor readings based on sensor details.
  delay(10000);
}

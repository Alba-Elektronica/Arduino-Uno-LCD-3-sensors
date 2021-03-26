/*
 * Alba Elektronica @ 2021 
 * IR test read serial input --> receiver  --> sensor -->  transmit data 
 * 
 * initialize LCD & temp / IR sensors
 * Loop pseudo code:
 *  1. IR receiver receives the signal from remote control
 *  2. Signals are displayed on the LCD display / Serial output
 *  3. Temperature sensor is read / activated  
 *  4. Temperature is displayed on LCD display / Serial output
 *  5. IR transmitter sends the temperature as a signal
 *  6. Signals are displayed on the LCD display / Serial output
 *  
 *  Pinout of the components:
 *  LCD pinout:
 *    A5  SCL, A4  SDA, 5V VCC, GND  GND 
 *    
 *  DHT11 KY-015 pinout:
 *    S  12,  +  3.3V,  -  GND 
 *    
 *  Infra-rood IR receiver KY- 022 (PWM signal)   
 *    - -> GND, + -> 3.3V, S -> 2
 *   
    Uses the arduino uno pinout ICSP header   
 *  Infra-rood IR transceiver KY - 005 (PWN signal)  
 *    - -> GND, + -> 5V, S -> 3
 *     
 */

#include <IRLibAll.h>
#include <IRLibRecvBase.h>
#include <IRLibSendBase.h>
#include <IRLib_HashRaw.h>
#include <IRLib_P01_NEC.h>
#include <IRLib_P02_Sony.h>
#include <IRLibCombo.h>     // After all protocols, include this


#include <LiquidCrystal_I2C.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//////////////////////////
//LCD 
LiquidCrystal_I2C lcd(0x27,16,2);

////////////////////////
// set pin KY - 015
#define pin_dht 12
#define DHTTYPE DHT11   // DHT 11
DHT_Unified dht(pin_dht, DHTTYPE);
float hum = 0.0;
float temp = 0.0;
//sensor_t sensor;

////////////////////////
//set pin KY - 005
#define pin_Ir_IN 3
IRsend IrSender;

///////////////////////////////
// set pin KY - 022
#define pin_Ir_Out 2
IRrecvPCI irRecv(pin_Ir_Out);

// initialize
void setup() {
  ////////////////
    // init serial output
    Serial.begin(9600);
    Serial.print("Start experiment");

    // init LCD 
    lcd.init();           // initialize the lcd 
    lcd.backlight();      // change light to verify
    lcd.setCursor(0,0);
    lcd.print("Start experiment");

    ////////////////////////////
    // init temp sensor KY - 015
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    Serial.println(F("Temperature Sensor"));
    Serial.print(sensor.max_value); Serial.println(F("°C"));
  
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print(sensor.max_value); Serial.println(F("%"));

    //KY - 022
     irRecv.enableIRIn();

}

void loop() {


  if (Serial.read() != -1) {
		  
		Serial.print("Hit any key of the remote");
		Serial.println();
  
		//2. Display request on LCD / serial
		lcd.setCursor(0,0);
		lcd.print("Hit any key of the remote");
		lcd.println();
  
		IrSender.send(NEC,0x61a0f00f,0);//NEC TV power button=0x61a0f00f
 
		///////////////////////////////////////
		//1. when data is received
		Serial.println("Request temperature reading"); 
    
		//2. Display request on LCD / serial
		lcd.setCursor(0,1); 
		lcd.print("Ir signal received");
		lcd.println();
   
		delay(200);// Receive the next value 
  
		/////////////////////////////
		//3. Reading temperature or humidity takes about 250 milliseconds!
		// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
		sensors_event_t event;
		dht.humidity().getEvent(&event);

		if (isnan(event.relative_humidity)) {
			Serial.println(F("Error reading humidity!"));
			hum = 0;
		} else {
			hum = event.relative_humidity;
    
			Serial.print(F("Humidity: "));
			Serial.print(event.relative_humidity);
			Serial.println(F("%"));
		}

		lcd.setCursor(0,0);
		lcd.print("Humidity: ");
		lcd.print(event.relative_humidity);
		lcd.print("%");
		lcd.println();
 
		// Read temperature as Celsius (the default)
		dht.temperature().getEvent(&event);

		//4. Display temperature on LCD / serial
		if (isnan(event.temperature)) {
			Serial.println(F("Error reading temperature!"));
			temp = 0;
		} else {
			temp = event.temperature;
    
			Serial.print(F("Temperature: "));
			Serial.print(event.temperature);
			Serial.println(F("°C"));
		}

		lcd.setCursor(0,1); 
		lcd.print("Temp: ");
		lcd.print(event.temperature);
		lcd.print("C");

		delay(200); // small delay to prevent reading errors
  
		///////////////////////////
		//5. it does not send and receive in the same time
		IrSender.send(hum, "Rev humidity", 1);
		IrSender.send(temp, "Temp", 2);
    
		//6. display the code on LCD / Serial
		Serial.println();
		Serial.print(F("Send now hum "));
		Serial.print(hum);
		Serial.print(F(" Send now temp"));
		Serial.print(temp);
		Serial.println();

		lcd.setCursor(0,0);
		lcd.print("Send hum");
		lcd.print(hum);
		lcd.println();
		lcd.setCursor(0,1);  
		lcd.print("Send now");
		lcd.print(temp);
		lcd.println();

		////////////////////
		//Stop sending & start receiving
		// reset receiving
		Serial.flush();

		delay(200);
	}
}

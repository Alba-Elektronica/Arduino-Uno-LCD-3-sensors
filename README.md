# Arduino-Uno-LCD-5-sensors
Experiments with sensors for Arduino-Uno-LCD-5-sensors kit

Each file corresponds to one combination Arduino Uno + LCD + one /two / three sensors.
Pinouts are specified in the corresponding file. 
For the experiments with three sensors, we have used also the power / GND pins of ICSP header.

Components:
 - Arduino Uno
 - Liquid Crystal Display (LCD) 1602 IIC I2C
 - 5 Sensors
  - DHT11 Temperature / Humidity Sensor
  - MH-RD Raindrops module
  - KY-018 Photosensitive module
  - KY-022 IR Infrared Sensor 
  - KY-005 IR Infrared Sensor
- Remote control
- connectors
- power cable for arduino

There is a short description of the pinout for each experiment in the header of each file. 
A brief description of the experiments:
1. DHT11-LCD - the humidity / temperature sensor. The temperature is displayed on both a serial monitor and an LCD.
2. MHRD-LCD  - the rain / water drops sensor. The input is displayed on both an LCD and the serial output.
3. MHRD-LCD-DHT11 - a combination of two experiments: the rain sensor and the humidity sensors. Results are displayed on an LCD and serial monitor. 
4. IRTest_receiver_read_transceiver - infrared sensors are combined with the humidity sensor. Input data in a serial monitor of Arduino will start the experiment. LCD the readings from experiments. 
5. IRTest_tranceiver_receiver - infrared sensors are combined with the humidity sensor. The experiment starts when pushing any key of the remote control.

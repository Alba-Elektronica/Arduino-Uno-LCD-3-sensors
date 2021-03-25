# Arduino-Uno-LCD-6-sensors
Experiments with sensors for Auduino-Uno-LCD-6-sensors kit

Each file corresponds to one combination Arduino Uno + LCD + one /two / three sensors.
Pinouts are specified in the corresponding file
For three sensors, we have used also the power / GND pins of ICSP header

Required components:
 - Arduino Uno
 - Liquid Crystal Display (LCD) 1602 IIC I2C
 - 6 Sensors
  - DHT11 Temperature / Humidity Sensor
  - MH-RD Raindrops module
  - KY-037 MH Microphone
  - KY-022 IR Infrared Sensor
  - KY-005 IR Infrared Sensor
  - KY-018 Photosensitive module
- connectors

There is a short description of the pinout for each experiment in the header of each file. 
A brief description of the experiments:
1. Micro-LCD - a microphone on the analog pin A0. The level of noise is outputed on LCD.
2. DHT11-LCD - the humidity / temperature sensor. The temperature is displaied on both a serial monitor and an LCD display.
3. MHRD-LCD  - the rain / water drops sensor. The input is displaied on both an LCD and the serial output.
4. MHRD-LCD-DHT11 - a combination between two experiments: the rain sensor and the humidity sensors. Results are displaied on an LCD and serial monitor. 
5. IRTest_receiver_read_tranceiver - ir test for infrared sensors combined with humidity sensors. LCD displays the readings.

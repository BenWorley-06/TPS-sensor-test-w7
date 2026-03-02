#include "HX711.h"

const uint8_t  DATA_PIN = 2;
const uint8_t CLOCK_PIN = 3;

HX711 pressure_sensor; // Sensor Object

void setup() {
  Serial.begin(115200);
  pressure_sensor.begin(DATA_PIN,CLOCK_PIN);
  pressure_sensor.set_offset(58269);
  pressure_sensor.set_scale(-84.412163); 
  pressure_sensor.tare();
}

void loop() {
  if (pressure_sensor.is_ready()){
    Serial.println(pressure_sensor.get_units(5));
    delay(250);
  }
}

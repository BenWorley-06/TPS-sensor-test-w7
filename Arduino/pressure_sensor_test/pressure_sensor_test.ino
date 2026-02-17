#include "HX711.h"

const uint8_t  DATA_PIN;
const uint8_t CLOCK_PIN;

HX711 pressure_sensor; // Sensor Object

void setup() {
  Serial.begin(115200);
  pressure_sensor.begin(DATA_PIN,CLOCK_PIN);
  pressure_sensor.set_offset(<calibrated value>);
  pressure_sensor.set_scale(<calibrated value>); 
  pressure_sensor.tare();
}

void loop() {
  if pressure_sensor.is_ready():
    Serial.println(pressure_sensor.get_units(5));
    delay(250);
}

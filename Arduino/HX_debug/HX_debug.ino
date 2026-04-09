#include "HX711.h"

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(2,3);
}

void loop() {
  Serial.println(scale.read());
  delay(200);
}
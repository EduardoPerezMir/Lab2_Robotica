#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725();

void setup() {
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("No se encontró el sensor.");
    while (1);
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Evitar división por cero
  if (c == 0) c = 1;

  float fr = (float)r / c;
  float fg = (float)g / c;
  float fb = (float)b / c;

  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);
  Serial.print(" C: "); Serial.println(c);

  String color = "Indefinido";

  if (c < 2) {
    color = "Negro";
  } else if (fr > fg + 0.15 && fr > fb + 0.15) {
    color = "Rojo";
  } else if (fg > fr + 0.10 && fg > fb + 0.10) {
    color = "Verde";
  } else if (fb > fr + 0.10 && fb > fg + 0.10) {
    color = "Azul";
  } else if (fr > 0.25 && fg > 0.25 && fb > 0.25 &&
             abs(fr - fg) < 0.05 && abs(fg - fb) < 0.05) {
    color = "Blanco";
  }

  Serial.print("Color detectado: ");
  Serial.println(color);

  delay(1000);
}
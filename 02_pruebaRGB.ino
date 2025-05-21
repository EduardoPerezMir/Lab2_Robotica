#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado correctamente.");
  } else {
    Serial.println("No se encontró el sensor TCS34725. Verifica las conexiones.");
    while (1);
  }

  tcs.setInterrupt(false); // Enciende el LED integrado 
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);
  Serial.print(" Clear: "); Serial.println(c);//cantidad de luz

  // Detecta el color predominante 
  String colorDetectado = detectarColor(r, g, b);
  Serial.print("Color detectado: ");
  Serial.println(colorDetectado);
  Serial.println("--------------------");

  delay(1000); 
}

String detectarColor(uint16_t r, uint16_t g, uint16_t b) {
  if (r > g && r > b) {
    return "Rojo";
  } else if (g > r && g > b) {
    return "Verde";
  } else if (b > r && b > g) {
    return "Azul";
  } else {
    return "Color indeterminado";
  }
}

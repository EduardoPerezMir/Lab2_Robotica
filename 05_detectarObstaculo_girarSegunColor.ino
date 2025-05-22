const int ENA = 10;
const int IN1 = 9;  
const int IN2 = 8; 

const int IN4 = 7;
const int IN3 = 6;
const int ENB = 5;
const int trigPin = 2;
const int echoPin = 3;
const int numLecturas = 10;  // Número de lecturas a promediar
const float UMBRAL_OBSTACULO = 10.0; 
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725();

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("No se encontró el sensor.");
    while (1);
  }
}

}
}

void avanzar(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

void retroceder(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

void girarDerecha(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

void girarIzquierda(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad);
  analogWrite(ENB, velocidad);
  delay(tiempo);
}

void detenerse(int tiempo) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(tiempo);
}
string medirColor(){
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
  return color;
}
float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); 
  
  if (duration == 0) {
    return -1; // No se detectó eco
  }

  float distancia = duration * 0.034 / 2;

  distancia += 2.0; // Compensación fija

  return distancia;
}

void loop() {

  avanzar(3000, 200);
  detenerse(3000);
  retroceder(3000, 200);
  detenerse(3000);
  girarDerecha(4000, 200);
  detenerse(3000);
  girarIzquierda(4000, 200);
  detenerse(5000);

  if (promedio => UMBRAL_OBSTACULO)avanzar(3000, 200);
  float suma = 0;
  int lecturasValidas = 0;

  for (int i = 0; i < numLecturas; i++) {
    float d = medirDistancia();
    if (d >= 0 && d < 400) { 
      suma += d;
      lecturasValidas++;
    }
    delay(50);
  }

  if (lecturasValidas > 0) {
    float promedio = suma / lecturasValidas;
    Serial.print("Distancia promedio corregida: ");
    Serial.print(promedio, 2);
    Serial.println(" cm");

    // Detección de obstáculo cercano
    if (promedio < UMBRAL_OBSTACULO) {
      Serial.println("⚠️ ¡Obstáculo detectado a menos de 10 cm!");
      detenerse(3000);
      if(medirColor()=="Rojo")retroceder(3000, 200);
      if(medirColor()=="Negro")girarDerecha(4000, 200);
      if(medirColor()=="Verde")girarIzquierda(4000, 200);
      if(medirColor()=="Indefinido")detenerse(3000);
    }

  } else {
    Serial.println("Sin lectura válida de ultrasonico");
  }

  delay(500);
}
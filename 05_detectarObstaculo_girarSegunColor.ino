#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int ENA = 10;
const int IN1 = 9;  
const int IN2 = 8;
const int IN4 = 7;
const int IN3 = 6;
const int ENB = 5;

const int trigPin = 2;
const int echoPin = 3;
const int numLecturas = 10;
const float UMBRAL_OBSTACULO = 35.0; 

Adafruit_TCS34725 tcs = Adafruit_TCS34725();

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);

  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado.");
  } else {
    Serial.println("No se encontró el sensor.");
    while (1);
  }
}

void avanzar(int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad); analogWrite(ENB, velocidad);
}

void retroceder(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad); analogWrite(ENB, velocidad);
  delay(tiempo);
}

void girarDerecha(int tiempo, int velocidad) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidad); analogWrite(ENB, velocidad);
  delay(tiempo);
}

void girarIzquierda(int tiempo, int velocidad) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidad); analogWrite(ENB, velocidad);
  delay(tiempo);
}

void detenerse(int tiempo) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  delay(tiempo);
}

String medirColor() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (c == 0) c = 1;

  float fr = (float)r / c;
  float fg = (float)g / c;
  float fb = (float)b / c;

  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);
  Serial.print(" C: "); Serial.print(c);
  Serial.print(" | fr: "); Serial.print(fr, 2);
  Serial.print(" fg: "); Serial.print(fg, 2);
  Serial.print(" fb: "); Serial.println(fb, 2);

  String color = "Indefinido";

  if (r == 0 && g == 0 && b == 0 && c < 2) {
    color = "Negro";
  }
  else if (fr > 0.3 && fg > 0.3 && fb > 0.3 &&
           abs(fr - fg) < 0.05 && abs(fg - fb) < 0.05) {
    color = "Blanco";
  }
  else if (fr >= fg && fr >= fb) {
      color = "Rojo";
    }
  // 4. VERDE: verde dominante
  else if (fg >= fr && fg >= fb) {
    color = "Verde";
  }
  // 5. AZUL: azul dominante
  else if (fb >= fr && fb >= fg) {
    color = "Azul";
  }

  Serial.print("Color detectado: ");
  Serial.println(color);
  return color;
}

float medirDistancia() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;

  float distancia = duration * 0.034 / 2;
  distancia += 2.0;
  return distancia;
}

void loop() {
  float suma = 0;
  int lecturasValidas = 0;

  for (int i = 0; i < numLecturas; i++) {
    float d = medirDistancia();
    if (d >= 0 && d < 400) {
      suma += d;
      lecturasValidas++;
    }
    delay(10);
  }

  if (lecturasValidas > 0) {
    float promedio = suma / lecturasValidas;
    Serial.print("Distancia promedio: ");
    Serial.print(promedio, 2);
    Serial.println(" cm");

    if (promedio >= UMBRAL_OBSTACULO) {
      avanzar(150);
    } else {
      Serial.println("⚠️ ¡Obstáculo detectado!");
      detenerse(3000);
      delay(100);
      String color = medirColor();

      if (color == "Rojo") retroceder(1400, 150);
      else if (color == "Negro") girarDerecha(490, 150);
      else if (color == "Verde") girarIzquierda(490, 150);
      else 
      {
        detenerse(2000);
      }
      detenerse(1000);

    }
    delay(500);

  } else {
    Serial.println("Sin lectura válida de ultrasónico");
  }
}

const int trigPin = 2;
const int echoPin = 3;
const int numLecturas = 10;  // Número de lecturas a promediar
const float UMBRAL_OBSTACULO = 10.0;  // Umbral para detección de obstáculo (en cm)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
    }

  } else {
    Serial.println("Sin lectura válida");
  }

  delay(500);
}

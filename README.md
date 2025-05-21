# Laboratorio 2 Robótica y Sistemas Autónomos

# Integrantes:
- Claudio Ignacio Cabello Vásquez
- David Samuel Martínez Canto
- Eduardo Andrés Pérez Miranda
  
# Laboratorio 2
## Tema: Sensores, Percepción y Planificación Básica con procesamiento de datos en Robótica Móvil.
Objetivos:
- Sensores y Percepción: Aprender a procesar los datos de los sensores (ultrasónico e IMU) mediante técnicas de filtrado y umbralización para mejorar la precisión de la percepción.
- Filtrado de señales: Aplicar técnicas básicas de filtrado para reducir el ruido en los datos obtenidos por los sensores.
- Umbralización: Definir umbrales adecuados para detectar obstáculos de manera más confiable.
- Planificación Básica: Realizar un control de navegación basado en la percepción filtrada y umbralizada para evitar obstáculos y en el color detectado.


## Materiales:
- Arduino UNO
- Chasis de robot móvil con dos motores DC basado en impresión 3D.
- Sensores (ultrasónicos, infrarrojo y RGB) para detección de obstáculos y color.
- Sensor IMU (MPU 6050) para medición de inclinación y giro.
- Batería y módulo de alimentación.
- Driver de motores (puente H) L298N o similar.
- Protoboard y cables de conexión.

##  Índice
1. [Resumen del Proyecto](#resumen-del-proyecto)
2. [Preguntas resueltas Parte 1](#preguntas-resueltas-parte-1)
3. [Documentación Parte 1](#documentación-parte-1)
4. [Preguntas resueltas Parte 2](#preguntas-resueltas-parte-2)
5. [Documentación Parte 2](#documentación-parte-2)
   

## Resumen del Proyecto


---


## Preguntas Resueltas Parte 1
1. ¿Qué es la percepción en robótica y por qué es fundamental en los sistemas autónomos?

Respuesta: Es la capacidad de un robot para adquirir, interpretar y utilizar datos sensoriales del entorno. Es fundamental porque permite la toma de decisiones y la interacción autónoma con el entorno.


2. En el sensor ultrasónico HC-SR04, ¿qué parámetro se mide para calcular la distancia?
   
Respuesta: El tiempo que tarda el eco del pulso ultrasónico en regresar al sensor.


3. ¿Cómo influye el ruido en las mediciones del sensor ultrasónico y cómo podría reducirse?

Respuesta: El ruido puede generar lecturas erróneas por ecos falsos o interferencias. Puede reducirse con filtrado de señales, promediado de lecturas y uso de algoritmos de detección de outliers.


---

## Documentación Parte 1

---

### 1. Conexión de los sensores ultrasónico HC-SR04 y RGB TCS34725 al Arduino

En esta parte del trabajo realizamos la conexión de dos sensores al Arduino UNO: el sensor ultrasónico **HC-SR04**, utilizado para la medición de distancia, y el sensor de color **TCS34725 (RGB)**, el cual detecta el color de superficies. A continuación, detallamos cómo fue realizada la conexión de cada uno de ellos.

#### Sensor ultrasónico HC-SR04

● El sensor ultrasónico **HC-SR04** fue conectado utilizando dos pines digitales para enviar y recibir señales de ultrasonido:

- El pin **TRIG** del sensor fue conectado al **pin digital 2** de Arduino UNO.
- El pin **ECHO** fue conectado al **pin digital 3** de Arduino UNO.
- El pin **VCC** fue conectado al **pin de 5V** del Arduino UNO.
- El pin **GND** fue conectado al **GND** del Arduino UNO.

● Este sensor emite una señal ultrasónica mediante el pin TRIG y luego mide el tiempo que tarda en volver por el pin ECHO. Con esto se calcula la distancia al objeto más cercano.

#### Sensor de color RGB TCS34725

● El sensor RGB **TCS34725**, que funciona con protocolo I2C, fue conectado a los pines analógicos de Arduino:

- El pin **SCL** del sensor fue conectado al **pin A5 (analógico 5)** de Arduino UNO.
- El pin **SDA** del sensor fue conectado al **pin A4 (analógico 4)** de Arduino UNO.
- El pin **VIN** fue conectado al **pin de 5V** del Arduino UNO.
- El pin **GND** fue conectado al **GND** del Arduino UNO.

● Este sensor permite identificar los niveles de rojo, verde, azul y la luz ambiente. La conexión I2C facilita su comunicación con el microcontrolador a través de los pines SDA y SCL.


### Organización en el protoboard

● Los pines **GND** de ambos sensores se conectaron a una línea común del protoboard, que compartía continuidad con el GND del Arduino.  
● De igual forma, los pines **VCC** y **VIN** de ambos sensores fueron conectados a una línea de 5V del protoboard alimentada directamente desde el pin de 5V del Arduino UNO.


**Tabla 1: Conexión Sensor Ultrasónico HC-SR04**

| Pin del Sensor | Conexión en Arduino UNO |
|----------------|-------------------------|
| TRIG           | Pin digital 2           |
| ECHO           | Pin digital 3           |

**Tabla 2: Conexión Sensor RGB TCS34725**

| Pin del Sensor | Conexión en Arduino UNO     |
|----------------|------------------------------|
| SCL            | Pin A5 (analógico 5)         |
| SDA            | Pin A4 (analógico 4)         |


---

### 2. Programar Arduino para leer la distancia con HC-SR04 y mostrarla en el monitor serie.

Se realizó una prueba utilizando el código 01_pruebaUltrasonico.ino, en el cual se programó el sensor ultrasónico HC-SR04 para medir distancias. Los valores obtenidos se muestran en el monitor serie de Arduino en tiempo real. Esta prueba permitió verificar el correcto funcionamiento del sensor y su capacidad para detectar objetos a diferentes distancias.

Link del video de la prueba en YouTube: https://www.youtube.com/shorts/hn_4I5e5PQ4

---

### 3. Programar Arduino para leer los valores RGB y mostrar el color detectado.


---

### 4. Analizar la precisión de los sensores en diferentes condiciones (luz, superficie, distancia).




## Preguntas Resueltas Parte 2
1. Si el robot detecta el color rojo en el suelo, ¿qué acción debería tomar? ¿Por qué?

Respuesta: Debería detenerse o cambiar de dirección, ya que el rojo puede indicar peligro o zona prohibida.


2. Si el sensor ultrasónico detecta valores erráticos, ¿qué estrategias podrías aplicar para mejorar la precisión?

Respuesta: Promediado de lecturas, filtrado Kalman o media móvil, y verificación con sensores redundantes.


3. Si tuvieras que integrar un nuevo sensor para mejorar la navegación del robot, ¿cuál elegirías y por qué?

Respuesta: Un sensor LiDAR por su alta precisión espacial y capacidad de mapear entornos en 2D/3D.


4. ¿Cuál es el tiempo de respuesta del robot al detectar un cambio de color?

Respuesta: Depende del microcontrolador, pero típicamente entre 10–100 ms.


---

## Documentación Parte 2

---

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

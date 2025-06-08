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

Se realizó la implementación del código 02_pruebaRGB.ino, cuyo objetivo fue leer los valores de color (Rojo, Verde y Azul) a través del sensor Adafruit TCS34725. Este sensor fue utilizado junto a la librería oficial de Adafruit, permitiendo obtener lecturas precisas de los componentes de color, así como el valor de luminosidad (canal Clear). Para verificar el correcto funcionamiento del sistema, se emplearon imágenes de colores primarios (rojo, verde y azul), observando que el sensor detectaba correctamente los colores dominantes según el caso. Esto permitió validar tanto el código como el hardware, asegurando una correcta lectura de los datos.

Link del video de prueba: https://www.youtube.com/shorts/BfJy00ZlzRA

---

### 4. Analizar la precisión de los sensores en diferentes condiciones (luz, superficie, distancia).

## Calibración y Pruebas del Sensor Ultrasónico

Durante la calibración del sensor ultrasónico **HC-SR04**, se realizaron pruebas de medición a distintas distancias conocidas: **25 cm**, **50 cm**, **75 cm** y **100 cm**. Para cada una de estas distancias se tomaron lecturas sin aplicar ningún tipo de corrección, obteniéndose los siguientes resultados:

| Distancia real (cm) | Medición sin corrección (cm) |
|---------------------|------------------------------|
| 25                  | 23.80                        |
| 50                  | 48.10                        |
| 75                  | 71.50                        |
| 100                 | 97.58                        |

Como se puede observar, las mediciones presentan un **error pequeño pero sistemático**, con una ligera subestimación de la distancia real. Por esta razón, se decidió mejorar la precisión implementando un promedio de **10 mediciones consecutivas**, descartando valores inválidos o fuera de rango. Además, se aplicó una **corrección fija de +2 cm** a cada lectura para compensar el sesgo identificado.

El resultado final, con la corrección aplicada y el promedio de 10 lecturas, fue el siguiente:

| Distancia real (cm) | Medición corregida (promedio + 2 cm) |
|---------------------|--------------------------------------|
| 25                  | 25.58                                |
| 50                  | 50.04                                |
| 75                  | 74.76                                |
| 100                 | 99.28                                |

Dado que el **margen de error resultante fue pequeño** (menor a 1 cm en todos los casos), se consideraron válidas estas mediciones para el funcionamiento del sistema.

Además, se realizaron pruebas adicionales midiendo la distancia hacia superficies de distintos materiales como **pared**, **cartón** y **plástico**, comprobando que las mediciones no variaban significativamente entre ellas. Esto confirma que el sensor es confiable bajo diferentes condiciones de superficie reflectante.

## Calibración y Pruebas del Sensor de Color TCS34725

Experimento 1: Lectura de Datos Crudos
En esta etapa se realizaron lecturas crudas del sensor utilizando objetos de colores estándar: rojo, verde, azul, blanco y negro. Para asegurar consistencia:

- Se mantuvo una distancia constante de 1 a 2 cm entre el sensor y la muestra.
- Se tomaron 10 lecturas por cada color.
- Se trabajó en un ambiente con luz controlada.
- El LED blanco del sensor estuvo encendido.

**Promedios aproximados de lecturas:**

| Color  | R    | G    | B    | C   |
| ------ | ---- | ---- | ---- | --- |
| Rojo   | 9    | 4    | 3    | 18  |
| Verde  | 3    | 5    | 3    | 11  |
| Azul   | 5    | 9    | 9    | 24  |
| Blanco | 17   | 21   | 16   | 54  |
| Negro  | 0.3  | 0.3  | 0.3  | 1   |

Experimento 2: Normalización de Valores RGB
Para mejorar la detección y compensar iluminación ambiental, se implementó la normalización RGB:

```
float fr = (float)r / c;
float fg = (float)g / c;
float fb = (float)b / c;
```

A partir de estos valores se observaron patrones consistentes:

Rojo: fr > 0.5

Verde: fg > 0.45

Azul: fb > 0.45

Blanco: fr, fg y fb > 0.25 y similares entre sí

Negro: c < 2 (muy poca luz)

Experimento 3: Clasificación de Colores
Se implementó un algoritmo lógico para clasificar colores usando los valores normalizados:

```
if (c < 2) {
    // Negro
} else if (fr > fg + 0.15 && fr > fb + 0.15) {
    // Rojo
} else if (fg > fr + 0.10 && fg > fb + 0.10) {
    // Verde
} else if (fb > fr + 0.10 && fb > fg + 0.10) {
    // Azul
} else if (fr > 0.25 && fg > 0.25 && fb > 0.25) {
    // Blanco
}
```
El sensor detecta de forma confiable los cinco colores bajo condiciones controladas.

La normalización RGB es fundamental para lograr precisión.

Se descartaron valores de lux y temperatura de color por no aportar a la discriminación efectiva.

El algoritmo final es robusto y efectivo en escenarios de uso básico.

## 5. analisis mejoras.

como mejoras podrían planificarse experimentos más exhaustivos como: variar sistemáticamente la intensidad y temperatura de la iluminación (luz cálida, luz fría, luz natural) para evaluar cómo cambian los umbrales de detección de color; probar la respuesta del TCS34725 ante mezclas de colores (por ejemplo amarillo, púrpura y cian) y diferentes matices intermedios; medir la precisión del HC-SR04 a distancias mayores (hasta su rango máximo) y contrastar resultados según ángulo de incidencia (objetos inclinados) y comparar superficies con texturas y reflectividades variadas (madera, metal cepillado, tela).


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

### 1. Aplicar umbralización al sensor ultrasónico para detectar si hay un obstáculo a menos de 10cm.

En el archivo 04_UltrasonicoCalibrado_conUmbral.ino se implementó correctamente la detección de obstáculos mediante la aplicación de un umbral de distancia. El sensor ultrasónico realiza múltiples mediciones, promediándolas para mejorar la precisión y reducir el ruido. Posteriormente, se compara la distancia promedio con un umbral definido (10 cm), de manera que cuando un objeto se encuentra a menos de esa distancia, el sistema reconoce la presencia de un obstáculo cercano y emite un mensaje de advertencia en el monitor serial. Esta técnica permite una detección fiable y estable, evitando falsos positivos causados por lecturas erráticas o valores atípicos, mejorando así el desempeño del sensor en aplicaciones prácticas.

---

### 2. Definir umbrales para detectar colores, rojo, verde y azul usando el sensor RGB.

Los umbrales para la detección de los colores rojo, verde y azul fueron definidos a partir de los resultados obtenidos en los experimentos realizados en la primera parte del laboratorio. En estos experimentos se analizaron y normalizaron las lecturas crudas del sensor RGB para distintos colores estándar, lo que permitió establecer rangos específicos para cada color. Estos umbrales están implementados y documentados en el código 03_RGBcalibrado.ino, que utiliza las lecturas normalizadas para identificar correctamente cada color con base en las condiciones definidas. Esta calibración garantiza una detección más precisa y confiable del sensor en distintas condiciones.

---

### 3. Implementar un algoritmo en Arduino que detenga el robot ante obstáculos y cambie de dirección según el color detectado.

Se implementó el algoritmo para que avanzara si no detectaba que estaba a menos de 10cm. En caso de que estuviera más cerca, realizaría lo siguiente: primero se detendría y mediría el color según el sensor RGB. Si es rojo, retrocedería; si es negro, giraría a la derecha; por el contrario, si es verde, giraría a la izquierda. En el caso de que el color sea indefinido, se detendrá por completo.  
La implementación de este código se puede ver en 05_detectarObstaculo_girarSegunColor.ino. En este código se reutilizó la calibración de ambos sensores, tanto el sensor RGB como el sensor ultrasónico, para que las mediciones sean lo más certeras posibles.

---

### 4. Probar navegación en un circuito con obstáculos y superficies en diferentes colores.

El algoritmo de navegación para circuitos con obstáculos y superficies de diferentes colores, denominado "05_detectarObstaculo_girarSegunColor.ino", controla el movimiento de un vehículo autónomo en función de su entorno. El vehículo dispone de cinco acciones: avanzar, retroceder, girar a la izquierda, girar a la derecha y detenerse.

Su comportamiento se basa en la detección de obstáculos y el análisis de color. Si hay espacio libre, avanza. En caso de encontrar un obstáculo, se detiene y evalúa el color de la superficie. Según el color detectado, adopta la siguiente respuesta:

Rojo: Retrocede.

Negro: Gira a la derecha.

Verde: Gira a la izquierda.

Otro color o sin identificación clara: Permanece detenido brevemente antes de continuar.
---

### 5. Ajustar parámetros para mejorar la detección y estabilidad del sistema.

Ajustar los parámetros en el codigo puede mejorar la detección de obstáculos, la precisión del reconocimiento de colores y la estabilidad del sistema. A continuacion algunos cambios y sus posibles efectos en base al codigo "05_detectarObstaculo_girarSegunColor.ino":

Mejorar la estabilidad de detección de distancia: Ajustar numLecturas, en el codigo se realizan 10 lecturas antes de calcular el promedio. Si se aumenta el número a 15 o 20, se reducira el impacto de lecturas erráticas del sensor ultrasónico

Optimizar la detección de colore: Modificar el umbral de color negro: Actualmente se evalua si (r == 0 && g == 0 && b == 0 && c < 2). Esto podría fallar si la iluminación es baja. En lugar de c < 2, intentar c < 5 para mejorar la detección en diferentes condiciones.

---

### 6. Implementación de estrategias de navegación basadas en reglas.

La Implementación de estrategias de navegación basadas en reglas se refleja en:

Si no hay obstáculos cerca, el vehículo avanza: Esto se determina comparando la distancia promedio con un umbral de seguridad. Si es mayor o igual, el vehículo sigue adelante.

Si hay un obstáculo cerca, el vehículo se detiene por 3 segundos y analiza el color del entorno: Se mide la distancia varias veces y si el promedio es menor al umbral, se detiene.

Dependiendo del color detectado, el vehículo reacciona de diferentes maneras:
Rojo: Retrocede por un tiempo determinado.
Negro: Gira a la derecha.
Verde: Gira a la izquierda.
Cualquier otro color: Se detiene durante 2 segundos.

Después de realizar una acción basada en el color, el vehículo se detiene brevemente antes de continuar: Esto evita movimientos bruscos y permite que vuelva a evaluar su entorno.

El proceso se repite continuamente: Se mide distancia, se actúa según las condiciones, y el vehículo sigue moviéndose en función de obstáculos y colores.

---

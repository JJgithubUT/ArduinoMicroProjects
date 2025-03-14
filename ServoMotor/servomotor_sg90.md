# ¿Para qué sirve el Servomotor SG90?

Este tipo de servomotores son utilizados en una gran variedad de proyectos de electrónica, robótica, carros de control remoto, aeronaves y más. Funcionan con la mayoría de tarjetas electrónicas de control con microcontroladores, como por ejemplo las tarjetas de **Arduino**, **Nodemcu**, **ESP32**, **PIC** y **Raspberry Pi**, entre otras.

## Especificaciones y características

- **Modelo:** SG90
- **Color:** Azul
- **Tamaño:** 22.8 mm x 12.3 mm x 22.5 mm
- **Peso:** 13 g
- **Grados/Ángulo de Rotación Máximo:** 0° a 180°
- **Engranajes:** Nylon
- **Temperatura de trabajo:** -30°C a +60°C
- **Voltaje de funcionamiento:** 4.8 VDC a 6 VDC (Recomendado: 5 VDC)

### Conexiones

- **Rojo:** Alimentación (+)
- **Café:** Alimentación (–) o tierra
- **Naranja:** Señal PWM

## Parámetros

- **servo:** Una variable de tipo Servo.
- **pin:** El número del pin al que el servo está conectado.
- **min** (opcional): Ancho del pulso (en microsegundos), corresponde al ángulo mínimo (0°) del servo (por defecto: 544).
- **max** (opcional): Ancho del pulso (en microsegundos), corresponde al ángulo máximo (180°) del servo (por defecto: 2400).

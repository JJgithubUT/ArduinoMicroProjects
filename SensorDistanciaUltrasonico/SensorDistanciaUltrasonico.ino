#include <ESP32Servo.h>

// Definimos los pines como constantes
const int pinEco = 5;
const int pinGatillo = 4;
const int pinServo = 2;

// Creamos el objeto Servo
Servo servo;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  // Configuramos el pin del emisor (Trig) como salida
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);  // Aseguramos que está apagado
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // Enviamos un pulso de 10 microsegundos
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Configuramos el pin del receptor (Echo) como entrada
  pinMode(echoPin, INPUT);
  
  // Medimos el tiempo de duración del pulso
  return pulseIn(echoPin, HIGH);
}

void manejarServo(int distancia, int umbral) {
  // Movemos el servomotor si la distancia está dentro del umbral
  if (distancia > 0 && distancia < umbral) {
    // Por ejemplo, mover a 90 grados
    servo.write(90);
    delay(500); // Un breve retraso
    servo.write(0); // Retorna a la posición inicial
  }
}

// Variables para control de tiempos
unsigned long tiempoAnterior = 0;
const int intervalo = 50; // Intervalo de actualización en milisegundos

void setup() {
  Serial.begin(115200);
  servo.attach(pinServo, 500, 2500); // Configuramos el servo
}

void loop() {
  unsigned long tiempoActual = millis();
  
  // Actualizamos la medición solo si ha pasado el intervalo
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    
    // Calculamos la distancia en centímetros
    int distancia = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    Serial.println(distancia); // Mostramos la distancia en el monitor serial

    // Llamamos a la función para manejar el servomotor
    manejarServo(distancia, 40); // Umbral de 40 cm
  }
}

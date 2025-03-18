#include <ESP32Servo.h>

// Definimos los pines como constantes
const int pinEco = 5;
const int pinGatillo = 4;
const int pinServo = 2;

// Creamos el objeto Servo
Servo servo;

// Variable para almacenar la última distancia medida
int ultimaDistancia = 0;

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
  if (distancia != ultimaDistancia && distancia > 0 && distancia < umbral) {
    // Movimiento al detectar el cambio
    servo.write(90); // Mover a 90 grados
    delay(500); // Breve retraso para mantener la posición
    servo.write(0); // Volver a 0 grados
    ultimaDistancia = distancia; // Actualizamos la última distancia
  }
}

void setup() {
  Serial.begin(115200);
  servo.attach(pinServo, 500, 2500); // Configuramos el servo
}

void loop() {
  // Calculamos la distancia en centímetros
  int distancia = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
  Serial.println(distancia); // Mostramos la distancia en el monitor serial

  // Llamamos a la función para manejar el servomotor
  manejarServo(distancia, 20); // Umbral de 20 cm
}

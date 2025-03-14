int pinLED = 2; // Pin donde está conectado el LED

void setup() {
  pinMode(pinLED, OUTPUT); // Configura el pin del LED como salida
}

void loop() {
  digitalWrite(pinLED, HIGH); // Enciende el LED
  delay(500); // Espera 500 milisegundos
  digitalWrite(pinLED, LOW); // Apaga el LED
  delay(500); // Espera 500 milisegundos
}

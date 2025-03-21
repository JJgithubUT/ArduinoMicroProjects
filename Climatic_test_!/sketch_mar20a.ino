#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN 27

#define LED1 2
#define LED2 4

int tiempoEspera = 5000; // Tiempo inicial en milisegundos

DHT dht(DHTPIN, DHTTYPE);

void detectarTemperatura() {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("ERROR EN EL SENSOR");
        return;
    }
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
}

void setup() {
    Serial.begin(9600);
    dht.begin();
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    Serial.println("Ingrese el tiempo de espera en milisegundos:");
}

void loop() {
    if (Serial.available()) {
        int nuevoTiempo = Serial.parseInt();
        if (nuevoTiempo > 0) {
            tiempoEspera = nuevoTiempo;
            Serial.print("Nuevo tiempo de espera: ");
            Serial.println(tiempoEspera);
        }
    }

    detectarTemperatura();

    digitalWrite(LED1, HIGH);
    delay(tiempoEspera);
    digitalWrite(LED1, LOW);

    detectarTemperatura();

    digitalWrite(LED2, HIGH);
    delay(tiempoEspera);
    digitalWrite(LED2, LOW);
}

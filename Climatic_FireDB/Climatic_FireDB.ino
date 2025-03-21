#include <DHT.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// 🔹 Configuración DHT
#define DHTTYPE DHT22
#define DHTPIN 27

#define LED1 2
#define LED2 4
#define LEDSENSOR 18

int tiempoEspera = 5000; // Tiempo inicial en milisegundos

DHT dht(DHTPIN, DHTTYPE);

// 🔹 Credenciales WiFi
#define WIFI_SSID "INFINITUM0350"
#define WIFI_PASSWORD "AQNnhapC6p"

// 🔹 Configuración de Firebase
#define FIREBASE_HOST "https://termostato-3ab33-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Dij9DkY9pW49EHfBF6Qvbw3BHM6QO97e1MhZE39b"

// 🔹 Objetos Firebase
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Función para leer la temperatura y subirla a Firebase
void detectarTemperatura() {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("ERROR EN EL SENSOR");
        return;
    }
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");

  
    // Subir temperatura a Firebase
    if (Firebase.setFloat(firebaseData, "/sensores/temperatura", temperature)) {
        Serial.println("✅ Temperatura subida: " + String(temperature));
    } else {
        Serial.println("❌ Error al subir temperatura: " + firebaseData.errorReason());
    }

    // Modificar y subir la temperatura actual del dispositivo
    if (Firebase.setFloat(firebaseData, "/Dispositivos/esp32trycsrp133/temp_actual_dis", temperature)) {
        Serial.println("✅ Temperatura actual del dispositivo subida: " + String(temperature));
    } else {
        Serial.println("❌ Error al subir temp_actual_dis: " + firebaseData.errorReason());
    }
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LEDSENSOR, OUTPUT);

    // Conectar a WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ Conectado a WiFi");

    // Configurar Firebase
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    // Iniciar Firebase
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("✅ Conectado a Firebase");
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

    // Detectar y subir temperatura
    detectarTemperatura();

    // Controlar LEDs con el tiempo de espera
    digitalWrite(LED1, HIGH);
    delay(tiempoEspera);
    digitalWrite(LED1, LOW);

    detectarTemperatura();

    digitalWrite(LED2, HIGH);
    delay(tiempoEspera);
    digitalWrite(LED2, LOW);

    delay(5000); // Espera 5 segundos antes de la siguiente lectura
}

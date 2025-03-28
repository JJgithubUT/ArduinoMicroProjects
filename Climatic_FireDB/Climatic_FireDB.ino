#include <DHT.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// 🔹 Configuración DHT
#define DHTTYPE DHT22
#define DHTPIN 27

#define LED1 33 // Esto es calor
#define LED2 32 // Esto es frío

int tiempoEspera = 5000; // Tiempo inicial en milisegundos
float temp_objetivo = 25.0; // Temperatura objetivo predeterminada

DHT dht(DHTPIN, DHTTYPE);

// 🔹 Credenciales WiFi
#define WIFI_SSID "UTT-Directores P"
#define WIFI_PASSWORD "D1r3ct0r3$%@"

// 🔹 Configuración de Firebase
#define FIREBASE_HOST "https://termostato-3ab33-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Dij9DkY9pW49EHfBF6Qvbw3BHM6QO97e1MhZE39b"

// 🔹 Objetos Firebase
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Función para leer la temperatura y realizar ajustes con base en `temp_objetivo_dis`
void detectarTemperatura() {
    float temperature = dht.readTemperature();
    if (isnan(temperature)) {
        Serial.println("❌ ERROR EN EL SENSOR");
        return;
    }

    Serial.print("Temperatura actual: ");
    Serial.print(temperature);
    Serial.println("°C");

    // Subir temperatura actual a Firebase
    if (Firebase.setFloat(firebaseData, "/esp32trycsrp133/temp_actual_dis", temperature)) {
        Serial.println("✅ Temperatura actual subida: " + String(temperature));
    } else {
        Serial.println("❌ Error al subir temp_actual_dis: " + firebaseData.errorReason());
    }

    // Obtener la temperatura objetivo desde Firebase
    if (Firebase.getFloat(firebaseData, "/esp32trycsrp133/temp_objetivo_dis")) {
        temp_objetivo = firebaseData.floatData();
        Serial.print("Temperatura objetivo obtenida: ");
        Serial.println(temp_objetivo);
    } else {
        Serial.println("❌ Error al obtener temp_objetivo_dis: " + firebaseData.errorReason());
    }

    // Ajuste de temperatura basado en `temp_objetivo`
    if (temperature < temp_objetivo) {
      digitalWrite(LED1, HIGH);  // Calor
      digitalWrite(LED2, LOW);   // Frío
      Serial.println("Calefacción encendida (LED1 ON)");
    } else {
      digitalWrite(LED1, LOW);   // Calor apagado
      digitalWrite(LED2, HIGH);  // Frío encendido
      Serial.println("Calefacción apagada (LED2 ON)");
    }

}

void setup() {
    Serial.begin(115200);
    dht.begin();
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    // Conectar a WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ Conectado a WiFi");

    // Configurar Firebase
    config.database_url = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("✅ Conectado a Firebase");
}

void loop() {
    detectarTemperatura(); // Detectar temperatura y realizar ajustes
    delay(tiempoEspera);   // Esperar el tiempo definido antes de la siguiente iteración
}

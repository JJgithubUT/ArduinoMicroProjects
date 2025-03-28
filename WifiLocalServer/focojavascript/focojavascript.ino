#include <WiFi.h>
#include <FirebaseESP32.h>

// 🔹 Configuración WiFi
#define WIFI_SSID "UTT-Directores P"
#define WIFI_PASSWORD "D1r3ct0r3$%@"

// 🔹 Configuración de Firebase
#define FIREBASE_HOST "https://arduinoclase-a2019-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "OxENbSUJHwKza1SG3NUqxhPTDApHHRpJMlKwlp8g" // Usa el Legacy Token si es necesario

// 🔹 Objetos Firebase
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

const int ledPin = 2; // LED conectado al pin 2

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

    // Conexión WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ Conectado a WiFi");

    // Configuración de Firebase
    config.database_url = FIREBASE_HOST; // Usar 'database_url' en lugar de 'host'
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("✅ Conectado a Firebase");
}

void loop() {
    Serial.println("Leyendo estado del LED desde Firebase...");

    if (Firebase.getBool(firebaseData, "/estado")) {
        if (firebaseData.dataType() == "boolean") {
            bool estado = firebaseData.boolData();
            digitalWrite(ledPin, estado ? HIGH : LOW);
            Serial.print("Estado del LED: ");
            Serial.println(estado ? "ENCENDIDO" : "APAGADO");
        } else {
            Serial.println("❌ El dato obtenido no es de tipo booleano.");
        }
    } else {
        Serial.print("❌ Error al obtener el estado: ");
        Serial.println(firebaseData.errorReason());
    }

    delay(2000);
}

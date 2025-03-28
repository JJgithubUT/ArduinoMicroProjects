#include <WiFi.h>  // Librería para manejar Wi-Fi
#include <FirebaseESP32.h> // Librería para Firebase

#define WIFI_SSID "TP-Link_E2B6" // Cambia por el nombre de tu red WiFi
#define WIFI_PASSWORD "14086298" // Cambia por la contraseña de tu red WiFi
#define FIREBASE_HOST "https://arduinoclase-a2019-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH ""  // No se requiere token de autenticación para tu configuración

FirebaseData firebaseData;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);

  // Conectar a Wi-Fi
  Serial.println("Conectando a Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Intentando conectar...");
  }
  Serial.println("Conectado a Wi-Fi!");

  // Configurar Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Inicializar Firebase
  Firebase.begin(&config, nullptr); // No se necesita autenticación
  Serial.println("Conexión a Firebase lista!");
}

void loop() {
  // Ejemplo: Escribir un valor en la base de datos
  if (Firebase.RTDB.setBool(&firebaseData, "/ruta_de_ejemplo", 123)) {
    Serial.println("Escritura exitosa en Firebase");
  } else {
    Serial.println("Error al escribir en Firebase");
    Serial.println(firebaseData.errorReason());
  }

  delay(5000); // Espera para no saturar las peticiones
}
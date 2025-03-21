#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Telepresencia";
const char* pass = "hola1234";

WebServer server(80);
const int ledPin = 2;

void inicio() {
    if (server.hasArg("led1") && server.arg("led1") == "on") {
        digitalWrite(ledPin, HIGH);
    }
    else if (server.hasArg("led1") && server.arg("led1") == "off") {
        digitalWrite(ledPin, LOW);
    }

    String html = "<html><body>";
    html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    html += "<title>Control del LED con ESP32</title>\n";
    html += "<h1>Control del LED</h1>";
    html += "<form method='get'>";
    html += "<button type='submit' name='led1' value='on'>Encender</button>";
    html += "<button type='submit' name='led1' value='off'>Apagar</button>";
    html += "</form>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);

    Serial.println("espere, conectando...");
    Serial.println("SSID: " + String(ssid));

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    // Intentamos conectar durante 30 segundos
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startAttemptTime >= 30000) { // Timeout de 30 segundos
            Serial.println("Error: No se pudo conectar a WiFi");
            return;
        }
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("wifi conectado a:");
    Serial.println(ssid);  
    Serial.println("Dirección IP asignada por el router: ");
    Serial.println(WiFi.localIP());

    server.on("/", inicio);
    server.begin();
}

void loop() {
    server.handleClient();
}

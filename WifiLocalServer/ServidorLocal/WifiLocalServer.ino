#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wifi";
const char* pass = "Contrasenya";

WebServer server(80);
const int ledPin = 2;

String getLEDState() {
  return digitalRead(ledPin) == HIGH ? "ENCENDIDO" : "APAGADO";
}

void inicio() {
  if (server.hasArg("led1")) {
    String ledValue = server.arg("led1");
    if (ledValue == "on") {
      digitalWrite(ledPin, HIGH);
    } else if (ledValue == "off") {
      digitalWrite(ledPin, LOW);
    }
  }

  String html = "<html><body>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  html += "<title>Control del LED Html con webserver y ESP32</title>\n";
  html += "<h1>Control del LED</h1>";
  html += "<h2>Estado del LED: " + getLEDState() + "</h2>";
  html += "<form method='get'>";
  html += "<button type='submit' name='led1' value=on>Encender</button>";
  html += "<button type='submit' name='led1' value=off>Apagar</button>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200); 
  Serial.println("espere, conectando...");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nError: No se pudo conectar a la red Wi-Fi.");
    return;
  }

  Serial.println("\nConectado a Wi-Fi");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", inicio);
  server.begin();
}

void loop() {
  server.handleClient();
}

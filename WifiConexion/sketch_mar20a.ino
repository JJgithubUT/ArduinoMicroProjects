#include <WiFi.h>

const char* ssid = "Red G";
const char* pass = "92242593";
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
WiFi.begin(ssid, pass);
delay(2000);
Serial.print("Se esta conectando a la red Wifi denominada");
Serial.println(ssid);
while(WiFi.status() !=WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
Serial.println("");
Serial.println("Wifi conectado");
Serial.println("Direccion IP: ");
Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}

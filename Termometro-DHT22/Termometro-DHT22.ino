#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN 27

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    delay(3000);
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if(isnan(humidity) || isnan(temperature)) {
      Serial.println("ERROR EN EL SENSOR");
      return;
    }

    /* Serial.print(" Humidity: ");
    Serial.print(humidity); */
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
}

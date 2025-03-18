#include <ESP32Servo.h>

Servo servo;
int pinServo = 2;
int delayTime = 15;

void setup() {
  servo.attach(pinServo, 500, 2500);
}

int pos = 0;

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);
    delay(delayTime);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(delayTime);
  }
}

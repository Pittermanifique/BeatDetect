#include <Arduino.h>


const int outputPin = 26;

void setup() {
  pinMode(outputPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    String ligne = Serial.readStringUntil('\n');
    if (ligne == "1") {
      digitalWrite(outputPin, HIGH);
    } else if(ligne == "0") {
      digitalWrite(outputPin, LOW);
    }
  }
}


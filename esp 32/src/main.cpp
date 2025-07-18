#include <M5Unified.h>
#include <Arduino.h>


const int outputPin = 26;

void setup() {
  // Initialize M5Stack
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("M5Stack StickC Plus2 Example");
  M5.Lcd.setCursor(0, 20);

  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    String ligne = Serial.readStringUntil('\n');
    if (ligne == "1") {
      M5.Lcd.clear();
      M5.Lcd.drawString("LED ON", 0, 20);
      digitalWrite(outputPin, LOW);
      digitalWrite(outputPin, HIGH);
    } else if(ligne == "0") {
      digitalWrite(outputPin, LOW);
      M5.Lcd.clear();
    }
  }
}


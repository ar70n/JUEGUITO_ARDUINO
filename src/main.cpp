#include <Arduino.h>

void setup() {
    Serial.begin(9600);
}

void loop() {
    if(Serial.available()) {
        while(Serial.available()) {
            char c = Serial.read();
            if (c != 0xffffffff) {
                Serial.print("I have received: ");
                Serial.println(c);
            }
        }
    }
    delay(500);
}
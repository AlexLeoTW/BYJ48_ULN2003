#include "BYJ48.hpp"

BYJ48 stepper(8, 9, 10, 11);
void setup() {
    Serial.begin(9600);
    stepper.setSpeed(100);
    stepper.step(512);
    delay(1000);
    stepper.step(-512);
    delay(1000);
}

void loop() {
    
}

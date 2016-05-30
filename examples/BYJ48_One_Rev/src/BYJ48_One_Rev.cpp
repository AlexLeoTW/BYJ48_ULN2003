#include "BYJ48.hpp"

BYJ48 stepper(8, 9, 10, 11);
void setup() {
    Serial.begin(9600);
    stepper.setSpeed(100);
    stepper.setStep(512);
    stepper.setStep(-512);
}

void loop() {
    stepper.move(512);
    delay(1000);
}

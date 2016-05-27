#include "BYJ48.hpp"

BYJ48 BYJ48(8, 9, 10, 11);

void setup() {
    Serial.begin(9600);
    stepper.setSpeed(100);
}

void loop() {
    stepper.step(512);
    delay(1000);
    stepper.step(-512);
    delay(1000);
}

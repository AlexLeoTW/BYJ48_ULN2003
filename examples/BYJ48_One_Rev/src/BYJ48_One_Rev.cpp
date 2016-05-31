#include "BYJ48.hpp"

//int nextStridePos(int curPos, bool curIsReverse);

BYJ48 stepper(8, 9, 10, 11);
void setup() {
    Serial.begin(9600);
    stepper.setSpeed(10);
    stepper.setStep(512);
    Serial.println("OK");
}

void loop() {
    stepper.move(1);
}

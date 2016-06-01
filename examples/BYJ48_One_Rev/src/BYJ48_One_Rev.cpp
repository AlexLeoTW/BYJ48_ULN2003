#include "BYJ48.hpp"

//int nextStridePos(int curPos, bool curIsReverse);

BYJ48 stepper(8, 9, 10, 11);
void setup() {
    Serial.begin(9600);
    stepper.setSpeed(10);
    Serial.println("OK");
}

void loop() {
    Serial.println("clockwise");
    stepper.addStep(STEP_PER_REV);
    stepper.revSync(STEP_PER_REV);
    delay(1000);
    Serial.println("conterclockwise");
    stepper.addStep(-STEP_PER_REV);
    stepper.revSync(STEP_PER_REV);
    delay(1000);
}

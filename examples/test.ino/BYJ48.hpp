/*
 * Stepper.h - Stepper library for Wiring/Arduino - Version 1.1.0
 *
 * Original library        from arduino.cc.
 *
 * The circuits can be found at
 *
 * http://www.arduino.cc/en/Tutorial/Stepper
 */

// ensure this library description is only included once
#ifndef BYJ48_hpp
#define BYJ48_hpp

#define STEP_PER_REV 512

class BYJ48 {
public:
    BYJ48() {
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
    }

    BYJ48(int in1, int in2, int in3,                          in4) {
        IN1 = in1;
        IN2 = in2;
        IN3 = in3;
        IN4 = in4;

        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
    }

    void setSpeed(long whatSpeed){}

    void step(int stepToTake) {
        if (stepToTake > 0) {
            isReverse = false;
        } else {
            isReverse = true;
        }

        for(int i=0; i<abs(stepToTake); i++) {
            stride();
            isReverse ? stepToTake++ : stepToTake--;
            delay(2);
        }
    }

private:
    int IN1 = 8;
    int IN2 = 9;
    int IN3 = 10;
    int IN4 = 11;
    bool isReverse = false;

    // SPEC: 1/64(5.625°) IMPLEMENT: 1/512
    void stride() {
        if (isReverse) {
            for (int i=7; i>=0; i--) {
                strideStage(i);
            }
        } else {
            for (int i=0; i<8; i++) {
                strideStage(i);
            }
        }
    }

    void strideStage(int stage) {
        switch(stage) {
            case 0:
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, HIGH);
            break;
            case 1:
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, HIGH);
            break;
            case 2:
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, LOW);
            break;
            case 3:
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, LOW);
            break;
            case 4:
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
            break;
            case 5:
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, HIGH);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
            break;
            case 6:
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
            break;
            case 7:
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, HIGH);
            break;
            default:
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
            break;
        }
    }
}

#endif

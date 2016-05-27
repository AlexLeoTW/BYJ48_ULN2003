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

#include "Arduino.h"
#define STEP_PER_REV 512
#define STRIDE_PER_STEP 8

class BYJ48 {

public:
    BYJ48() {
        IN1 = 8;
        IN2 = 9;
        IN3 = 10;
        IN4 = 11;
        stride_delay = 2;
        curIsReverse = false;
        curStridePos = 0;

        initPin();
    }

    BYJ48(int in1, int in2, int in3, int in4) {
        IN1 = in1;
        IN2 = in2;
        IN3 = in3;
        IN4 = in4;
        stride_delay = 2;
        curIsReverse = false;
        curStridePos = 0;

        initPin();
    }

    void setSpeed(int targetRPM) {
        stride_delay = 60 * 1000000 / STEP_PER_REV / STRIDE_PER_STEP / targetRPM;
        Serial.println(stride_delay);
    }

    void step(int number_of_steps) {
        int stepToTake = abs(number_of_steps);

        if (number_of_steps > 0) {
            curIsReverse = false;
        } else {
            curIsReverse = true;
        }

        while (stepRemain > 0) {
            takeStep();
        }
    }

private:
    int IN1;    // = 8
    int IN2;    // = 9
    int IN3;    // = 10
    int IN4;    // = 11
    int stride_delay;
    bool curIsReverse;
    unsigned long lastTick;
    int curStridePos;


    void initPin() {
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
    }

    bool tick() {
        if (micros() - lastTick >= stride_delay) {
            return true;
        } else {
            return false;
        }
    }

    void takeStep() {
        for (int i=0; i<8; i++) {
            while (takeStride(i)) {}
        }
    }

    bool takeStride(int ctrlCode) {
        if (tick()) {
            curStridePos = nextStridePos(curStridePos);
            fireCtelCode();
        }
    }

    int nextStridePos(int curPos) {
        if (curPos+1 < STRIDE_PER_STEP && !curIsReverse) {
            return curPos++;
        } else if (curPos+1 >= STRIDE_PER_STEP && !curIsReverse) {
            return 0;
        } else if (curPos-1 >= 0 && curIsReverse) {
            return curPos--;
        } else if (curPos-1 < 0 && curIsReverse) {
            return 7;
        }
    }

    void fireCtelCode() {
        switch(curPos) {
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
};

#endif
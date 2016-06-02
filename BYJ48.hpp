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
#define STEP_PER_REV 64
#define GEAR_RATIO 64
#define CW_DIRETION_CNT 8

class BYJ48 {

public:
    BYJ48() {
        IN1 = 8;
        IN2 = 9;
        IN3 = 10;
        IN4 = 11;
        strideDelayMicros = 2;
        curStepPos = 0;
        stepsToTake = 0;

        initPin();
    }

    BYJ48(int in1, int in2, int in3, int in4) {
        IN1 = in1;
        IN2 = in2;
        IN3 = in3;
        IN4 = in4;
        strideDelayMicros = 2;
        curStepPos = 0;
        stepsToTake = 0;

        initPin();
    }

    void setSpeed(int targetRPM) {
        strideDelayMicros = 60L * 1000000L / STEP_PER_REV / GEAR_RATIO / targetRPM;
        Serial.println(strideDelayMicros);
    }

    void addStep(int number_of_steps) {
        stepsToTake += number_of_steps*GEAR_RATIO;
    }

    bool tick() {
        if (micros() - lastTick >= strideDelayMicros) {
            lastTick = micros();
            return true;
        } else {
            return false;
        }
    }

    void revSync(int step) {
        step *= GEAR_RATIO;

        Serial.print("move(");
        Serial.print(step);
        Serial.println(")");
        Serial.print(stepsToTake);
        Serial.println(" steps to take");

        while(step>0 && stepsToTake!=0) {
            if (rev()) {
                delayMicroseconds(strideDelayMicros);
                step--;
            }
        }
    }

    bool rev() {
        if (tick() && stepsToTake != 0) {
            curStepPos = nextPos(curStepPos);
            fireCtelCode(curStepPos);
            if (stepsToTake > 0) {
                stepsToTake--;
            } else {
                stepsToTake++;
            }
            return true;
        } else {
            return false;
        }
    }

private:
    int IN1;    // = 8
    int IN2;    // = 9
    int IN3;    // = 10
    int IN4;    // = 11
    unsigned long strideDelayMicros;
    unsigned long lastTick;
    int curStepPos;
    int stepsToTake;


    void initPin() {
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
    }

    int nextPos(int curPos) {
        if (curPos+1 < CW_DIRETION_CNT && stepsToTake > 0) {
            return curPos+1;
        } else if (curPos+1 >= CW_DIRETION_CNT && stepsToTake > 0) {
            return 0;
        } else if (curPos-1 >= 0 && stepsToTake < 0) {
            return curPos-1;
        } else if (curPos-1 < 0 && stepsToTake < 0) {
            return 7;
        } else {
            Serial.print("ERROR @");
            Serial.println(curPos);
        }
    }

    void fireCtelCode(int stepPos) {
        switch(stepPos) {
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

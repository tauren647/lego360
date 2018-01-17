
#pragma once

#include <Servo.h>

#include "L_Pins.hpp"

Servo servo;

class L_Servo {

private:
    const int stepDelay = 30;

    int minAngle;
    int maxAngle;
    int lastRotate = 0; // 0-up, 1-down
    int servoPosition;

public:
    L_Servo(int minAngle, int maxAngle) {
        // servo init
        this->minAngle = minAngle;
        this->maxAngle = maxAngle;
        servoPosition = this->minAngle;
        
        servo.attach(L_Pins::pin_servo);
        servo.write(servoPosition);
    }

    void vertical_round(int degree) {
        if (degree > servoPosition) {
            if (lastRotate == 1)
                degree += 20;
            lastRotate = 0;

            for (int i = servoPosition; i < servoPosition + degree; i += 1) {
                servo.write(i);
                delay(stepDelay);
            }
            servoPosition = servoPosition + degree;
        }
        else {
            if (lastRotate == 0)
                degree -= 20;
            lastRotate = 1;

            for (int i = servoPosition; i > servoPosition + degree; i -= 1) {
                servo.write(i);
                delay(stepDelay);
            }
      
            servoPosition = servoPosition + degree;
        }
    }
};

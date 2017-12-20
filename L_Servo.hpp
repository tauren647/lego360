
#pragma once

#include <Servo.h>

#include "L_Pins.hpp"

class L_Servo {

private:
    static Servo servo;

    static const int stepDelay_ = 30;

    static int minAngle_;
    static int maxAngle_;
    static int lastRotate_ = 0; // 0-up, 1-down
    static int currentPosition_;

public:
    static void attach(int minAngle, int maxAngle) {
        minAngle_ = minAngle;
        maxAngle_ = maxAngle;
        currentPosition_ = minAngle_;
        
        servo.attach(L_Pins::pin_servo);
        servo.write(currentPosition_);
    }

    static void vertical_round(int degree) {
        if (degree > currentPosition_) {
            if (lastRotate_ == 1)
                degree += 20;
            lastRotate_ = 0;

            for (int i = currentPosition_; i < currentPosition_ + degree; i += 1) {
                servo.write(i);
                delay(stepDelay_);
            }
            currentPosition_ = currentPosition_ + degree;
        }
        else {
            if (lastRotate_ == 0)
                degree -= 20;
            lastRotate_ = 1;

            for (int i = currentPosition_; i > currentPosition_ + degree; i -= 1) {
                servo.write(i);
                delay(stepDelay_);
            }
      
            currentPosition_ = currentPosition_ + degree;
        }
    }
};


#pragma once

#include "L_Pins.hpp"

class L_Stepper {

private:
    const int stepDelay_ = 4;
    const double k_ = 2.77; // step koeficient 2.75

    void step(int activePin) {
        int pinVector[] = { L_Pins::pin_step1, L_Pins::pin_step2, L_Pins::pin_step3, L_Pins::pin_step4 };
        for (int pin : pinVector) {
            if (pin == activePin)
                digitalWrite(pin, HIGH);
            else
                digitalWrite(pin, LOW);
        }
    }

    void stop() {
        digitalWrite(L_Pins::pin_step1, LOW);
        digitalWrite(L_Pins::pin_step2, LOW);
        digitalWrite(L_Pins::pin_step3, LOW);
        digitalWrite(L_Pins::pin_step4, LOW);
    }

    void right() {
        int pinVector[] = { L_Pins::pin_step1, L_Pins::pin_step2, L_Pins::pin_step3, L_Pins::pin_step4 };
        for (int pin : pinVector) {
            step(pin);
            delay(stepDelay_);
        }
    }

    void left() {
        int pinVector[] = { L_Pins::pin_step4, L_Pins::pin_step3, L_Pins::pin_step2, L_Pins::pin_step1 };
        for (int pin : pinVector) {
            step(pin);
            delay(stepDelay_);
        }
    }

public:
    L_Stepper() {
        pinMode(L_Pins::pin_step1, OUTPUT);
        pinMode(L_Pins::pin_step2, OUTPUT);
        pinMode(L_Pins::pin_step3, OUTPUT);
        pinMode(L_Pins::pin_step4, OUTPUT);
    }

    void horizontal_round(double degree) {
        degree *= k_; //6.5
        
        for (int i = 0; i < 2; i++) {
            for (int i = 0; i < degree; i++) {
                right();
            }
        }
        stop();
        delay(100*stepDelay_);
    }
};


/*
class L_Stepper {

private:
    // pins
    const int pin1 = 2;
    const int pin2 = 4;
    const int pin3 = 8;
    const int pin4 = 7;

    const int stepDelay = 4;
    const double k = 2.77; // step koeficient 2.75

public:
    L_Stepper() {
        // stepper init
        pinMode(pin1, OUTPUT);
        pinMode(pin2, OUTPUT);
        pinMode(pin3, OUTPUT);
        pinMode(pin4, OUTPUT);
    }

    void horizontal_round(double degree) {
        degree *= k; //6.5
        
        for (int i = 0; i < 2; i++) {
            for (int i = 0; i < degree; i++) {
                right();
            }
        }
        stop_stepper();
    }

    void stop_stepper() {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        delay(100*stepDelay);
    }

    void right() {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        delay(stepDelay);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        delay(stepDelay);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        delay(stepDelay);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        delay(stepDelay);
    }
      
    void left() {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
        delay(stepDelay);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
        delay(stepDelay);
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        delay(stepDelay);
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, LOW);
        delay(stepDelay);
    }
};
*/
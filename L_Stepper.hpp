
#include "L_Pins.hpp"

class L_Stepper {

private:
    static const int stepDelay_ = 4;
    static const double k_ = 2.77; // step koeficient 2.75

    static void step(int activePin) {
        for (int pin : { L_Pins::pin_step1, L_Pins::pin_step2, L_Pins::pin_step3, L_Pins::pin_step4 }) {
            if (pin == activePin)
                digitalWrite(pin, HIGH);
            else
                digitalWrite(pin, LOW);
        }
    }

    static void stop() {
        digitalWrite(L_Pins::pin_step1, LOW);
        digitalWrite(L_Pins::pin_step2, LOW);
        digitalWrite(L_Pins::pin_step3, LOW);
        digitalWrite(L_Pins::pin_step4, LOW);
    }

    static void right() {
        for (int pin : { L_Pins::pin_step1, L_Pins::pin_step2, L_Pins::pin_step3, L_Pins::pin_step4 }) {
            step(pin);
            delay(stepDelay_);
        }
    }

    static void left() {
        for (int pin : { L_Pins::pin_step4, L_Pins::pin_step3, L_Pins::pin_step2, L_Pins::pin_step1 }) {
            step(pin);
            delay(stepDelay_);
        }
    }

public:
    static void attach() {
        pinMode(L_Pins::pin_step1, OUTPUT);
        pinMode(L_Pins::pin_step2, OUTPUT);
        pinMode(L_Pins::pin_step3, OUTPUT);
        pinMode(L_Pins::pin_step4, OUTPUT);
    }

    static void horizontal_round(double degree) {
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

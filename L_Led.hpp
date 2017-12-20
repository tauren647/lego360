
#include "L_Pins.hpp"
#include "L_Color.hpp"

class L_Led {
  
private:

public:
    static void attach() {
        // led init
        pinMode(L_Pins::pin_r, OUTPUT);
        pinMode(L_Pins::pin_g, OUTPUT);
        pinMode(L_Pins::pin_b, OUTPUT);
    }

    static void indication(Color color) {
        digitalWrite(L_Pins::pin_r, LOW);
        digitalWrite(L_Pins::pin_g, LOW);
        digitalWrite(L_Pins::pin_b, LOW);

        switch (color) {
        case Color::None:
            break;
        case Color::Red:
            digitalWrite(L_Pins::pin_r, HIGH);
            break;
        case Color::Green:
            digitalWrite(L_Pins::pin_g, HIGH);
            break;
        case Color::Blue:
            digitalWrite(L_Pins::pin_b, HIGH);
            break;
        case Color::Cyan:
            digitalWrite(L_Pins::pin_g, HIGH);
            digitalWrite(L_Pins::pin_b, HIGH);
            break;
        }
    }
};

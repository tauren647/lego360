
class L_Led {
  
private:
    // pins
    const int r = 11;
    const int g = 12;
    const int b = 3;

public:
    const int NONE = 0;
    const int RED = 1;
    const int GREEN = 2;
    const int BLUE = 3;
    const int CYAN = 4;

    L_Led() {
        // led init
        pinMode(r, OUTPUT);
        pinMode(g, OUTPUT);
        pinMode(b, OUTPUT);
    }

    void indication(int color) {
        digitalWrite(r, LOW);
        digitalWrite(g, LOW);
        digitalWrite(b, LOW);

        switch (color) {
        case 0:
            break;
        case 1:
            digitalWrite(r, HIGH);
            break;
        case 2:
            digitalWrite(g, HIGH);
            break;
        case 3:
            digitalWrite(b, HIGH);
            break;
        case 4:
            digitalWrite(g, HIGH);
            digitalWrite(b, HIGH);
            break;
        }
    }
};

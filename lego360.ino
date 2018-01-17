
#include <SoftwareSerial.h>

#include "L_Pins.hpp"
#include "L_Color.hpp"
#include "L_Shooter.hpp"

const int minServoAngle = 30;  // servo limit position
const int maxServoAngle = 180;

// pins
SoftwareSerial* bluetooth;

L_Servo* l_servo;
L_Stepper* l_stepper;
L_Led* l_led;
L_Shooter* l_shooter;

enum class L_State  {
    Idle, Running
};

L_State state = L_State::Idle;
int photoRemain = 0;

void setup() {
    // led init
    l_led = new L_Led();

    l_led->indication(Color::Red);
    delay(2000);

    // init
    /////////////

    // init bluetooth module
    bluetooth = new SoftwareSerial(L_Pins::pin_tx, L_Pins::pin_rx); // set bluetooth module (TX, RX)
    bluetooth->begin(9600);
    bluetooth->println("/Init BT ok");
    
    // wait for bluetooth connection
    String input = "";
    while(true) {
        while (!(bluetooth->available() > 0)) {
            l_led->indication(Color::None);
            delay(500);
            l_led->indication(Color::Blue);
            delay(500);
        }

        input = readInput();//String(bluetooth->readString());
        //bluetooth->println("> " + input);
        if (input == "ok")
            break;
    }
    l_led->indication(Color::None);
    delay(500);
    bluetooth->println("/Lego 360 connected!");
    
    // servo init
    l_servo = new L_Servo(minServoAngle, maxServoAngle);

    // stepper init
    l_stepper = new L_Stepper();
    l_stepper->horizontal_round(10);
    delay(200);

    // HID keyboard init
    Serial.begin(9600);
    randomSeed(analogRead(0));
    delay(200);

    // start
    /////////////    
    bluetooth->println("/Initialization done");
    bluetooth->println("/======================");
    bluetooth->println("Menu");
    bluetooth->println("-Enter mode (360, pano)");
    bluetooth->flush();
}

String readInput() {
    char input[32] = "\0";
    char character;
    int i = 0;
    while (bluetooth->available() > 0) {
        character = bluetooth->read();
        if (character == '\n' || character == '\r') {
            input[i] = '\0';
            break;
        }

        input[i] = character;
        i++;
    }

    bluetooth->flush();

    return input;
}

void loop() {
    if (bluetooth->available() > 0) {
        String mode = readInput();
        bluetooth->println("> " + mode);

        if (state == L_State::Idle && mode == "360") {
            bluetooth->println("Menu > Mode 360");
            l_shooter = new L_Shooter(l_servo, l_stepper, l_led, 12, 6);
            state = L_State::Running;
            photoRemain = 12*6;
        }
        else if (state == L_State::Idle && mode == "pano") {
            bluetooth->println("Menu > Mode pano");
            // TODO
        }
        else if (mode == "stop") {
            state = L_State::Idle;
            bluetooth->println("Menu");
            bluetooth->println("-Enter mode (360, pano)");
        }
        else {
            bluetooth->println("/Bad command");
            bluetooth->println("/======================");
            if (state == L_State::Idle) {
                bluetooth->println("Menu");
                bluetooth->println("-Enter mode (360, pano)");
            }
            bluetooth->flush();
        }
    } else if (state == L_State::Running) {
        if (photoRemain > 0) {
            bluetooth->println(l_shooter->shoot());
            photoRemain--;
        } else {
            bluetooth->println("/360 finished");
            bluetooth->println("/======================");
            bluetooth->println("Menu");
            bluetooth->println("-Enter mode (360, pano)");
            state = L_State::Idle;
        }
    } else {
        l_led->indication(Color::Green);
        delay(500);
        l_led->indication(Color::None);
        delay(400);
    }

    bluetooth->flush();
    delay(100);
}
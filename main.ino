
#include <SoftwareSerial.h>

#include "L_Shooter.hpp"

const int minServoAngle = 30;  // servo limit position
const int maxServoAngle = 180;

// pins
SoftwareSerial bluetooth(5, 6); // set bluetooth module (TX, RX)

L_Servo* l_servo;
L_Stepper* l_stepper;
L_Led* l_led;
L_Shooter* l_shooter;

void setup() {
    // led init
    l_led = new L_Led();

    l_led->indication(l_led->RED);
    delay(2000);

    // init
    /////////////

    // init bluetooth module
    bluetooth.begin(9600);
    
    // wait for bluetooth connection
    do {
        l_led->indication(l_led->NONE);
        delay(500);
        l_led->indication(l_led->BLUE);
        delay(500);
    } while(bluetooth.available() > 0 && bluetooth.readString() == "ok");
    delay(500);
    bluetooth.println("Lego 360 connected!");
    
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
    
    bluetooth.println("Initialization done");
    bluetooth.println("======================");
    bluetooth.println("Enter mode (360, pano)");

    /*
    delay(2000);
    l_led->indication(l_led->NONE);

    // start
    /////////////
    l_shooter = new L_Shooter(l_servo, l_stepper, l_led, 6, 2);
    for (int i = 0; i < 6*2; i++)
        l_shooter->shoot();

    l_servo->vertical_round(minServoAngle);
    */
}

void loop() {
    while (true) {
        if (bluetooth.available() > 0) {
            String mode = bluetooth.readString();

            if (mode == "360") {
            }
            else if (mode == "pano") {

            }
            else {
                bluetooth.println("Bad command");
                bluetooth.println("======================");
                bluetooth.println("Enter mode (360, pano)");
            }
        }

        delay(100);
    }
}
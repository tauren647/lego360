
//#pragma once

#include <SoftwareSerial.h>

#include "L_Pins.hpp"
#include "L_Shooter.hpp"
#include "L_Color.hpp"

//#define TX 5
//#define RX 6

const int minServoAngle = 30;  // servo limit position
const int maxServoAngle = 180;

SoftwareSerial bluetooth; // set bluetooth module (TX, RX)

void setup() {
    // led init
    L_Led::attach();
    L_Led::indication(Color::Red);
    delay(2000);

    // init
    /////////////

    // init bluetooth module
    bluetooth(L_Pins::pin_tx, L_Pins::pin_rx);
    bluetooth.begin(9600);
    
    // wait for bluetooth connection
    do {
        L_Led::indication(Color::None);
        delay(500);
        L_Led::indication(Color::Blue);
        delay(500);
    } while(bluetooth.available() > 0 && bluetooth.readString() == "ok");
    delay(500);
    bluetooth.println("Lego 360 connected!");
    
    // servo init
    L_Servo::attach(minServoAngle, maxServoAngle);

    // stepper init
    L_Stepper::attach();
    L_Stepper::horizontal_round(10);
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
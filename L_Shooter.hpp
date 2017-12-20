
#pragma once

#include "L_Pins.hpp"
#include "L_Servo.hpp"
#include "L_Stepper.hpp"
#include "L_Led.hpp"

class L_Shooter {

private:
	const int volumeUpCode = 0x80;    // vol up keyboard code
	uint8_t buf[8] = { 0 };   // keyboard report buffer

	const int minServoAngle_ = 30;  // servo limit position
	const int maxServoAngle_ = 180;

	// TODO maxServoAngle vMaxAngle ????

	int hCount_; // count of photos
	int vCount_;

	int hAngle = -1; // photographed angle for panorama mode
	int vMinAngle;
	int vMaxAngle;

	int hDiff; // diff angle between photos
	int vDiff;

	int hDone = 0;
	int vDone = 0;

	void send_key() {
	  	buf[2] = volumeUpCode;    // send character
	  	Serial.write(buf, 8);   // Send keypress
	  
	  	buf[0] = 0;
	  	buf[2] = 0;
	  	Serial.write(buf, 8); // Release key  
	}

public:
	L_Shooter(int hCount, int vCount)
			: hCount_(hCount), vCount_(vCount) {

		hDiff = 360 / hCount;
		vDiff = (maxServoAngle_ - minServoAngle_) / (vCount - 1); // -1 bacause 90 and 2 photos = 1*90 deg
	}

	L_Shooter(int hCount, int vCount, int hAngle, int vMinAngle, int vMaxAnlge)
			: L_Shooter(hCount, vCount), hAngle(hAngle), vMinAngle(vMinAngle), vMaxAngle(vMaxAnlge) {

		hDiff = hAngle / (hCount - 1);
		vDiff = (vMaxAngle - vMinAngle) / (vCount - 1);
	}

	String shoot() {
		delay(2500);
		send_key(); // take a photo
		delay(4000);

		if (vDone == vCount_ || (vDone == 0 && hCount_ % 2 != 0)) {
			// horizontal rotate
			l_stepper_.horizontal_round(hDiff);
			hDone += 1;
			vDone = 0;
			
		}
		else {
			// vertical rotate
			if (hDone % 2 == 0) {
				// vertical rotate UP
				l_servo_.vertical_round(vDiff * vDone);
				
			}
			else
				// vertical rotate DOWN
				l_servo_.vertical_round(maxServoAngle_ - (vDiff * vDone));

			vDone += 1;
		}

		String output = "";
		for (int i = 0; i < hDone; i++)
			output += "#";
		output += vDone;
		for (int i = 0; i < (hCount_-hDone-1); i++)
			output += "_";

		return output;
	}
};
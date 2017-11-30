#include "L_Servo.hpp"
#include "L_Stepper.hpp"
#include "L_Led.hpp"

class L_Shooter {

private:
	const int volumeUpCode = 0x80;    // vol up keyboard code
	uint8_t buf[8] = { 0 };   // keyboard report buffer

	L_Servo* l_servo;
	L_Stepper* l_stepper;
	L_Led* l_led;

	const int minServoAngle = 30;  // servo limit position
	const int maxServoAngle = 180;

	// TODO maxServoAngle vMaxAngle ????

	int hCount; // count of photos
	int vCount;

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
	L_Shooter(L_Servo* ser, L_Stepper* step, L_Led* led, int hCount, int vCount) {
		l_servo = ser;
		l_stepper = step;
		l_led = led;

		this->hCount = hCount;
		this->vCount = vCount;

		hDiff = 360 / hCount;
		vDiff = (maxServoAngle - minServoAngle) / (vCount - 1); // -1 bacause 90 and 2 photos = 1*90 deg
	}

	L_Shooter(L_Servo* ser, L_Stepper* step, L_Led* led, int hCount, int vCount, int hAngle, int vMinAngle, int vMaxAnlge) {
		l_servo = ser;
		l_stepper = step;
		l_led = led;

		this->hCount = hCount;
		this->vCount = vCount;
		this->hAngle = hAngle;
		this->vMinAngle = vMinAngle;
		this->vMaxAngle = vMaxAngle;

		hDiff = hAngle / (hCount - 1);
		vDiff = (vMaxAngle - vMinAngle) / (vCount - 1);
	}

	String shoot() {
		delay(2500);
		send_key(); // take a photo
		delay(4000);

		if (vDone == vCount || (vDone == 0 && hCount % 2 != 0)) {
			// horizontal rotate
			l_stepper->horizontal_round(hDiff);
			hDone += 1;
			vDone = 0;
			
		}
		else {
			// vertical rotate
			if (hDone % 2 == 0) {
				// vertical rotate UP
				l_servo->vertical_round(vDiff * vDone);
				
			}
			else
				// vertical rotate DOWN
				l_servo->vertical_round(maxServoAngle - (vDiff * vDone));

			vDone += 1;
		}

		String output = "";
		for (int i = 0; i < hDone; i++)
			output += "#";
		output += vDone;
		for (int i = 0; i < (hCount-hDone-1); i++)
			output += "_";

		return output;
	}
};
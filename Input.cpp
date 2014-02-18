#include "Input.h"

Input::Input(Joystick* _stick, OctocanumDrive* _drive)
{
	stick = _stick;
	drive = _drive;
	dance = false;
}

void Input::Update()
{

	float x = stick->GetRawAxis(_MEC_X);
	float y = stick->GetRawAxis(_MEC_Y);
	float r = stick->GetRawAxis(_MEC_R);
	bool drop = stick->GetRawButton(_DROP);
	bool dance = stick->GetRawButton(_DANCE_ENABLE);

	SmartDashboard::PutNumber("X-Axis", x);
	SmartDashboard::PutNumber("Y-Axis", y);
	SmartDashboard::PutNumber("Rotation", r);
	SmartDashboard::PutBoolean("Drop", drop);
	SmartDashboard::PutBoolean("Dance", dance);

	if (x < 0.1 && x > -0.1)
		x = 0.0;
	if (y < 0.1 && y > -0.1)
		y = 0.0;
	if (r < 0.1 && r > -0.1)
		r = 0.0;
	
	drive->Drive(x, y, r);
	
	if (dance) {
		drive->valve0->Set(stick->GetRawButton(_DANCE_LEFT));
		drive->valve1->Set(stick->GetRawButton(_DANCE_RIGHT));
	} else {
		if (drop) drive->Drop();
		else drive->Raise();
	}



	/*if (stick->GetRawButton(5))
	{ //Toggle button override mode (left)
		buttonOverride = !buttonOverride;
	}

	
	
	if (!buttonOverride)
	{ //Trigger mode
		if (down < -0.5) drive->Raise();
		else drive->Drop();
	}
	else
	{ //Button mode
		if (stick->GetRawButton(6))
		{ //Toggle mecanum mode
			ifMecanum = !ifMecanum;
		}
		
		if (ifMecanum) drive->Raise(); //Mecanum
		else drive->Drop(); //Traction
	}*/
}

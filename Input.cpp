#include "Input.h"

Input::Input(Joystick* newStick, OctocanumDrive* newDrive)
{
	stick = newStick;
	drive = newDrive;
	ifMecanum = true;
	buttonOverride = false; //Start with toggle disable
	eggMode = false;
}

void Input::Update()
{
	float x = 0, y = 0, r = 0, down = 0;
	//try {
		x = stick->GetRawAxis(STRAFE_X);
		y = stick->GetRawAxis(STRAFE_Y);
		r = stick->GetRawAxis(ROTATE);
		down = stick->GetRawAxis(MODE_TOGGLE);
	//} catch (...) {}
	if (x < 0.1 && x > -0.1)
		x = 0;
	if (y < 0.1 && y > -0.1)
		y = 0;
	if (r < 0.1 && r > -0.1)
		r = 0;
	
	drive->Drive(x, y, r);
	
	SmartDashboard::PutNumber("X-Axis", x);
	SmartDashboard::PutNumber("Y-Axis", y);
	SmartDashboard::PutNumber("Rotation", r);
	SmartDashboard::PutBoolean("Mecanum mode: ", ifMecanum);
	SmartDashboard::PutBoolean("buttonOverride: ", buttonOverride);
	
	if (stick->GetRawButton(5))
	{ //Toggle button override mode (left)
		buttonOverride = !buttonOverride;
	}
	if (stick->GetRawButton(9) && stick->GetRawButton(10)) drive->toggleEgg();
	
	
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
		
		if (ifMecanum)
		{ //Actually get around to switching wheels.
			drive->Raise(); //Mecanum
		}
		else drive->Drop(); //Traction
	}
}

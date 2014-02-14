#include "Input.h"

Input::Input(Joystick* newStick, OctocanumDrive* newDrive)
{
	stick = newStick;
	drive = newDrive;
}

void Input::Update()
{
	float x = 0, y = 0, z = 0
	float down = false;
	try {
		x = stick->GetRawAxis(STRAFE_X);
		y = stick->GetRawAxis(STRAFE_Y);
		r = stick->GetRawAxis(ROTATE);
		down = stick->GetRawAxis(MODE_TOGGLE);
	} catch (...) {}
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
	
	if (down < -0.5)
		drive->Drop();
	else
		drive->Raise();
}

#include "Input.h"

Input::Input(Joystick* newStick, OctocanumDrive* newDrive)
{
	stick = newStick;
	drive = newDrive;
}

void Input::Update()
{
	float x = stick->GetRawAxis(STRAFE_X);
	float y = stick->GetRawAxis(STRAFE_Y);
	float r = stick->GetRawAxis(ROTATE);
	
	if (x < 0.1 && x > -0.1)
		x = 0;
	if (y < 0.1 && y > -0.1)
		y = 0;
	if (r < 0.1 && r > -0.1)
		r = 0;
	
	drive->Drive(-x, -y, r);
	
	SmartDashboard::PutNumber("x", x);
	
	if (stick->GetRawAxis(MODE_TOGGLE) < -0.5)
		drive->Raise();
	else
		drive->Drop();
}

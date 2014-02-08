#include "Input.h"

Input::Input(Joystick* newStick, OctocanumDrive* newDrive)
{
	stick = newStick;
	drive = newDrive;
}

void Input::Update()
{
	drive->Drive(
		stick->GetRawAxis(STRAFE_X),
		stick->GetRawAxis(STRAFE_Y),
		stick->GetRawAxis(ROTATE)
	);
	
	//if (stick->GetRawButton(MODE_TOGGLE))
		//drive->Toggle();
	if (stick->GetRawAxis(MODE_TOGGLE) < -0.5)
		drive->Raise();
	else
		drive->Drop();
}

#include "Input.h"

Input::Input(Joystick* _stick, OctocanumDrive* _drive)
{
	stick = _stick;
	drive = _drive;
}

void Input::Update()
{
	drive->Drive(
		stick->GetRawAxis(STRAFE_X),
		stick->GetRawAxis(STRAFE_Y),
		stick->GetRawAxis(ROTATE)
	);
	
	
	SmartDashboard::PutNumber("Stafe_x: ", stick->GetRawAxis(STRAFE_X));
	SmartDashboard::PutNumber("Stafe_y: ", stick->GetRawAxis(STRAFE_Y));
	SmartDashboard::PutNumber("rot: ", stick->GetRawAxis(ROTATE));
	SmartDashboard::PutBoolean("button: ", stick->GetRawButton(MODE_TOGGLE));
	
	if (stick->GetRawButton(MODE_TOGGLE))
		drive->Toggle();
}

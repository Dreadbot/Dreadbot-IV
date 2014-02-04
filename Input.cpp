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
 }

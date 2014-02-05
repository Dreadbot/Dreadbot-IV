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
 	
 	if (stick->GetRawAxis(MODE_TRACTION)) {
 		drive->Drop();
 	}
 	if (stick->GetRawAxis(MODE_MECANUM)) {
 		drive->Raise();
 	}
 }

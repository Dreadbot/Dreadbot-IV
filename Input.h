#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"

	#define PROFILE_1
	#ifdef PROFILE_1
		const int MODETOGGLE = 0;
		const int SETUPSHOOT = 1;
		const int FIRE = 2;
		const int STRAFE_X = 1;
		const int STRAFE_Y = 2;
		const int ROTATE = 3;
	#endif

class Input 
{
	Joystick * stick;
	OctocanumDrive* drive;
	public:
		Input(Joystick* _stick, OctocanumDrive* _drive);
		void Update();
};

#endif

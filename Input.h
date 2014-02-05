#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"


static const uint32_t MODETOGGLE = 0;
static const uint32_t SETUPSHOOT = 1;
static const uint32_t FIRE = 2;
static const uint32_t STRAFE_X = 1;
static const uint32_t STRAFE_Y = 2;
static const uint32_t ROTATE = 3;


class Input 
{
	Joystick * stick;
	OctocanumDrive* drive;
	public:
		Input(Joystick* _stick, OctocanumDrive* _drive);
		void Update();
};

#endif

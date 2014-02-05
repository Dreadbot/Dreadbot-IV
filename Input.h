#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"

// Buttons
static const uint32_t MODE_TOGGLE = 1;

// Axii
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

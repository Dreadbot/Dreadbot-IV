#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"

// Buttons
//static const uint32_t MODE_TOGGLE = 1;
static const uint32_t MODE_TOGGLE = 3;

// Axii
static const uint32_t STRAFE_X = 4;
static const uint32_t STRAFE_Y = 5;
static const uint32_t ROTATE = 1;


class Input 
{
	Joystick* stick;
	OctocanumDrive* drive;
public:
	Input(Joystick* newStick, OctocanumDrive* newDrive);
	void Update();
};

#endif

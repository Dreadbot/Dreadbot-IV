#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"

// Buttons
//static const uint32_t MODE_TOGGLE = 1;
static const uint32_t MODE_TOGGLE = 3;

// Axii
static const uint32_t STRAFE_X = 2;
static const uint32_t STRAFE_Y = 1;
static const uint32_t ROTATE = 4;


class Input 
{
	Joystick* stick;
	OctocanumDrive* drive;
	
	bool eggMode;
	bool ifMecanum;
	bool buttonOverride; //Is the user using the trigger or the bumper?
public:
	Input(Joystick* newStick, OctocanumDrive* newDrive);
	void Update();
};

#endif

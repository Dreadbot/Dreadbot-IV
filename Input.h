#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"

#define _PROFILE1
#define _DIRECTMODE_Lf310

#ifdef _DIRECTMODE_Lf310
	#define _BUTTON_A 2
	#define _BUTTON_B 3
	#define _BUTTON_X 1
	#define _BUTTON_Y 4
	#define _BUTTON_LB 5
	#define _BUTTON_RB 6
	#define _BUTTON_LT 7
	#define _BUTTON_RT 8
	#define _BUTTON_START 9
	#define _BUTTON_BACK 10
	#define _BUTTON_LJOY 11
	#define _BUTTON_RJOY 12
	#define _AXIS_LJOY_X 1
	#define _AXIS_LJOY_Y 2
	#define _AXIS_RJOY_X 3
	#define _AXIS_RJOY_Y 4
	#define _AXIS_DPAD_X 5
	#define _AXIS_DPAD_Y 6
#endif

#ifdef _PROFILE1
	#define _MEC_X _AXIS_LJOY_X
	#define _MEC_Y _AXIS_LJOY_Y
	#define _MEC_R _AXIS_RJOY_X
	#define _ARC_Y _AXIS_LJOY_Y
	#define _ARC_R _AXIS_RJOY_X
	#define _DROP _BUTTON_RT 	// Activate the secondary drive mode
	#define _SET _BUTTON_LT 	// Switch the default drive mode

	#define _WINDUP 0
	#define _FLIPPER 0
	#define _TRIGGER 0

	#define _DANCE_LEFT _BUTTON_LB
	#define _DANCE_RIGHT _BUTTON_RB
	#define _DANCE_ENABLE _BUTTON_A
#endif




class Input 
{
	Joystick* stick;
	OctocanumDrive* drive;
	
public:
	Input(Joystick* _stick, OctocanumDrive* _drive);
	void Update();
protected:
	bool dance;
};

#endif

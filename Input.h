#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"
#include "armControl.h"
#include "Shooter.h"

#define PROFILE1
#define DIRECTMODE_Lf310

#ifdef DIRECTMODE_Lf310
	#define BUTTON_A 2
	#define BUTTON_B 3
	#define BUTTON_X 1
	#define BUTTON_Y 4
	#define BUTTON_LB 5
	#define BUTTON_RB 6
	#define BUTTON_LT 7
	#define BUTTON_RT 8
	#define BUTTON_START 10
	#define BUTTON_BACK 9
	#define BUTTON_LJOY 11
	#define BUTTON_RJOY 12
	#define AXIS_LJOY_X 1
	#define AXIS_LJOY_Y 2
	#define AXIS_RJOY_X 3
	#define AXIS_RJOY_Y 4
	#define AXIS_DPAD_X 5
	#define AXIS_DPAD_Y 6
#endif

#ifdef PROFILE1
	#define MEC_X AXIS_LJOY_X //Movement controls
	#define MEC_Y AXIS_LJOY_Y
	#define MEC_R AXIS_RJOY_X
	#define ARC_Y AXIS_LJOY_Y
	#define ARC_R AXIS_RJOY_X 
	#define DROP BUTTON_RT

	#define FLIPPER AXIS_LJOY_Y //Shooter controls
	#define TRIGGER BUTTON_B
	#define ARMS AXIS_DPAD_Y
	#define ARM_MECS AXIS_RJOY_Y

	#define DANCE_LEFT BUTTON_LB //Dancing controls
	#define DANCE_RIGHT BUTTON_RB
	#define DANCE_ENABLE BUTTON_A
#endif

class Input 
{
public:
	Input(Joystick* newStick, 
		Joystick* newP2Stick,
		OctocanumDrive* newDrive, 
		armControl* newArms,
		Shooter* newShooter);
	void Update();
private:
	Joystick* stick;
	Joystick* p2Stick;
	OctocanumDrive* drive;
	armControl* arms;
	Shooter* shooter;
	bool dance;
};
#endif

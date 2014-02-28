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

// Driver controls
	#define MEC_X AXIS_LJOY_X 
	#define MEC_Y AXIS_LJOY_Y
	#define MEC_R AXIS_RJOY_X
	#define ARC_Y AXIS_LJOY_Y
	#define ARC_R AXIS_RJOY_X 
	#define DROP BUTTON_RT
	#define RAGE_MODE BUTTON_START

// Shooter controls
	#define FLIPPER AXIS_RJOY_Y 
	#define TRIGGER BUTTON_A
	#define ARMS AXIS_LJOY_Y
	#define ARM_MECS_IN BUTTON_LT
	#define ARM_MECS_OUT BUTTON_RT
	#define SHOOTER_RESET BUTTON_B

// Dance controls (on driver joystick)
	#define DANCE_ENABLE BUTTON_Y
	#define DANCE_LEFT BUTTON_LB 
	#define DANCE_RIGHT BUTTON_RB

#endif


class Input 
{
public:
	Input(Joystick* _driveStick, 
		Joystick* _shootStick,
		OctocanumDrive* _drive, 
		ArmControl* _arms,
		Shooter* _shooter);

	void Update();

private:
	Joystick* driveStick;
	Joystick* shootStick;

	OctocanumDrive* drive;
	ArmControl* arms;
	Shooter* shooter;

	bool dance;
};

#endif

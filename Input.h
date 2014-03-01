#ifndef _INPUT_H_
#define _INPUT_H_

#include "WPIlib.h"
#include "OctocanumDrive.h"
#include "ArmControl.h"
#include "Shooter.h"

#define PROFILE1
#define DIRECTMODE_DMODE
#define DIRECTMODE_XMODE

#ifdef DIRECTMODE_DMODE
	#define D_BUTTON_A 2
	#define D_BUTTON_B 3
	#define D_BUTTON_X 1
	#define D_BUTTON_Y 4
	#define D_BUTTON_LB 5
	#define D_BUTTON_RB 6
	#define D_BUTTON_LT 7
	#define D_BUTTON_RT 8
	#define D_BUTTON_START 10
	#define D_BUTTON_BACK 9
	#define D_BUTTON_LJOY 11
	#define D_BUTTON_RJOY 12
	#define D_AXIS_LJOY_X 1
	#define D_AXIS_LJOY_Y 2
	#define D_AXIS_RJOY_X 3
	#define D_AXIS_RJOY_Y 4
	#define D_AXIS_DPAD_X 5
	#define D_AXIS_DPAD_Y 6
#endif

#ifdef DIRECTMODE_XMODE
	#define X_BUTTON_A 1
	#define X_BUTTON_B 2
	#define X_BUTTON_X 3
	#define X_BUTTON_Y 4
	#define X_BUTTON_LB 5
	#define X_BUTTON_RB 6
	#define X_BUTTON_START 8
	#define X_BUTTON_BACK 7
	#define X_BUTTON_LJOY 9	
	#define X_BUTTON_RJOY 10
	#define X_AXIS_TRIGGERS 3
	#define X_AXIS_LJOY_X 1
	#define X_AXIS_LJOY_Y 2
	#define X_AXIS_RJOY_X 4
	#define X_AXIS_RJOY_Y 5
	#define X_AXIS_DPAD_X 6
#endif

#ifdef PROFILE1

// Driver controls
	#define MEC_X D_AXIS_LJOY_X 
	#define MEC_Y D_AXIS_LJOY_Y
	#define MEC_R D_AXIS_RJOY_X
	#define ARC_Y D_AXIS_LJOY_Y
	#define ARC_R D_AXIS_RJOY_X 
	#define DROP D_BUTTON_RT
	#define RAGE_MODE D_BUTTON_START

// Shooter controls
	#define FLIPPER X_AXIS_RJOY_Y 
	#define TRIGGER X_BUTTON_A
	#define ARMS X_AXIS_LJOY_Y
	#define ARM_MECS X_AXIS_TRIGGERS
	#define SHOOTER_RESET X_BUTTON_B

// Dance controls (on driver joystick)
	#define DANCE_ENABLE D_BUTTON_Y
	#define DANCE_LEFT D_BUTTON_LB 
	#define DANCE_RIGHT D_BUTTON_RB
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

#include "WPILib.h"
#include <math.h>


#define Robot_1 // Profile
#define TEST_WATCHDOG // Enables the watchdog in test mode



//#define TEST_MATCHSIM // Test mode simulates a match
//#define TEST_AUTON // Test mode simulates autonomous mode
//#define TEST_TELEOP // Test mode simulates tele-op period
#define TEST_FREEDRIVE // Test mode allows free tele-op-esque control of the robot without tele-op time limits



#ifdef ROBOT_1 // Robot-specific parameters go here.
	const uint AUTON_PERIOD = 60 // Seconds: Length of the autonomous period
	const uint TELEOP_PERIOD = 90 // Seconds: Length of the teleoperated period
	const double LRATE = 0.1 // Seconds: Refresh rate of the constrol loops (has to be under half a second)
	#define chDRV_FL 2; // PWM channel; controls the drive motor of the front-left swerve module.
	#define chDRV_FR 3;
	#define chDRV_RL 4;
	#define chDRV_RR 5;
	#define chSWV_FL 6; // PWM channel; controls the swerve motor of the front-left swerve module.
	#define chSWV_FR 7;
	#define chSWV_RL 8;
	#define chSWV_RR 9;
	#undef ROBOT_1
#endif

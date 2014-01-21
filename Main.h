#include "WPILib.h"
#include <math.h>

const uint AUTON_PERIOD = 60 // Seconds: Length of the autonomous period
const uint TELEOP_PERIOD = 90 // Seconds: Length of the teleoperated period
const double LRATE = 0.034 // Seconds: Refresh rate of the constrol loops (has to be under half a second)

#define TEST_WATCHDOG
//#define TEST_MATCHSIM // Simulate a full match
//#define TEST_AUTON // Simulate autonomous
//#define TEST_TELEOP // Simulate tele-op w/time constraints
#define TEST_FREEDRIVE // Tele-op-esque control of the robot without timed cutoff


#define PRF_0
#ifdef PRF_0

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

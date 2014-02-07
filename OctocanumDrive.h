#ifndef OCTOCANUMDRIVE_H_
#define OCTOCANUMDRIVE_H_

#include "WPILib.h"
#include <math.h>

const double maxOutput = 1.0;
const uint8_t syncGroup = 0x80;

struct OctocanumModule {
	//Solenoid *valve;
	Talon *motor;
	
	OctocanumModule(uint8_t i)
	{
		motor = new Talon(i);
	}
};

class OctocanumDrive 
{
	OctocanumModule *drive[4];

	bool tractionMode;
	bool enabled;
	bool phaseChange;
	typedef enum 
	{
		kFrontLeft,
		kFrontRight,
		kRearLeft,
		kRearRight
	};


	void SetOutputs(float leftOutput, float rightOutput);
	void Normalize(double *wheelSpeeds);
	void RotateVector(double &x, double &y, double angle);
	float Limit(float num);

	void MechanumDrive(float x, float y, float rotation, float gyroAngle);
	void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs);
public:
	OctocanumDrive();

	void Enable();
	void Disable();
	void Drop();
	void Raise();
	bool GetMode();
	bool GetEnabled();
	void Toggle();//toggle the mode

	void Drive(float x, float y, float rotation);
};

#endif

#ifndef OCTOCANUMDRIVE_H_
#define OCTOCANUMDRIVE_H_

#include "WPILib.h"
#include <math.h>

float maxOutput = 0.5;

struct OctocanumModule
{
	Valve *valve;
	Talon *motor;
	
	OctocanumModule(uint8_t i, uint8_t vTop, uint8_t vBottom)
	{
		motor = new Talon(i);
		valve = new Valve(vTop, vBottom);
		
	}
};

// This is actually a thing
class Valve
{
	Solenoid *s0;
	Solenoid *s1;
	open = false;
	
public:
	Valve(uint8_t p_s0, uint8_t p_s1)
	{
		s0 = new Solenoid(p_s0);
		s1 = new Solenoid(p_s1);
	}
	
	bool GetOpen() 
	{
		return open;
	}
	
	void Open() 
	{
		s0->Set(true);
		s1->Set(false);
	}
	
	void Close() 
	{
		s0->Set(false);
		s1->Set(true);	
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

	void Drive(float x, float y, float rotation);
};

#endif

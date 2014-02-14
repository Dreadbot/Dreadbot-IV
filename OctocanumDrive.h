#ifndef OCTOCANUMDRIVE_H_
#define OCTOCANUMDRIVE_H_

#include "WPILib.h"
#include <math.h>


// This is actually a thing
class Valve
{
	Solenoid *s0;
	Solenoid *s1;
	bool open;
	
public:
	Valve(uint8_t p_s0, uint8_t p_s1)
	{
		open = false;
		s0 = new Solenoid(p_s0);
		s1 = new Solenoid(p_s1);
	}
	
	bool GetOpen() 
	{
		return open;
	}
	
	void Set(bool v) 
	{
		s1->Set(!v);
		s0->Set(v);
	}
};

struct OctocanumModule
{
	//Valve *valve;
	Talon *motor;
	
	OctocanumModule(uint8_t i, uint8_t vTop, uint8_t vBottom)
	{
		motor = new Talon(i);
		//valve = new Valve(vTop, vBottom);
		
	}
};

class OctocanumDrive 
{
	OctocanumModule *drive[4];
	
	float maxOutput;
	bool tractionMode;
	bool enabled;
	bool phaseChange;
	Valve *valve;
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

#ifndef OCTOCANUMDRIVE_H_
#define OCTOCANUMDRIVE_H_

#define _PIDTUNE

#include "WPILib.h"
#include  "Valve.h"
#include <math.h>


struct OctocanumModule
{
	Talon *motor;
	Encoder *encoder;
	PIDController *speedController;

	OctocanumModule(uint8_t motorCh, uint8_t encoderACh, uint8_t encoderBCh, bool reverse)
	{
		motor = new Talon(motorCh);

		encoder = new Encoder(encoderACh, encoderBCh);
		encoder->SetReverseDirection(reverse);
		encoder->SetDistancePerPulse(1.44);
			// for traction, 0.05027
			// for mecanum, 0.07540
		//encoder->SetMinRate(2);
		encoder->SetPIDSourceParameter(encoder->kRate);

		speedController = new PIDController(0.1, 0, 0, encoder, motor, 0.05);
		speedController->SetInputRange(720.0, -720.0);
		speedController->SetOutputRange(-0.5, 0.5);
	}
};

class OctocanumDrive
{
	OctocanumModule *drive[4];
	bool tractionMode;
	bool enabled;
	bool dance;

	typedef enum 
	{
		kFrontLeft,
		kFrontRight,
		kRearLeft,
		kRearRight
	};

	double wheelSpeeds[4];


	void SetOutputs(float leftOutput, float rightOutput);
	void Normalize();
	void RotateVector(double &x, double &y, double angle);
	float Limit(float num);

	void MechanumDrive(float x, float y, float rotation);
	void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs);
	
	void Set();
public:
	Valve *valve0;
	Valve *valve1;
	
	double maxOutput;
	
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

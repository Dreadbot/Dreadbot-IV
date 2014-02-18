#ifndef OCTOCANUMDRIVE_H_
#define OCTOCANUMDRIVE_H_

#include "WPILib.h"
#include <math.h>
#include "Valve.h"


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
		encoder->SetMinRate(2.0);
		//encoder->SetPIDSourceParameter(2);

		speedController = new PIDController(1.0, 1.0, 0.0, encoder, motor);
		speedController->SetInputRange(-720.0, 720.0);
		speedController->SetOutputRange(-1.0, 1.0);
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
	void Normalize(double *wheelSpeeds);
	void RotateVector(double &x, double &y, double angle);
	float Limit(float num);

	void MechanumDrive(float x, float y, float rotation);
	void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs);
	
public:
	Valve *valve0;
	Valve *valve1;

	float maxOutput;
	
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

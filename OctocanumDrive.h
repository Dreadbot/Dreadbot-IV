#ifndef OCTOCANUMDRIVE_H_
#define OCTOCANUMDRIVE_H_


#include "WPILib.h"
#include  "Valve.h"
#include <cmath>



class OctocanumModule
{
public:
	Talon *motor;
	Encoder *encoder;
	PIDController *cloop;

	OctocanumModule(uint8_t motorCh, uint8_t encoderACh, uint8_t encoderBCh, bool reverse)
	{
		motor = new Talon(motorCh);
		encoder = new Encoder(encoderACh, encoderBCh);
		encoder->SetReverseDirection(reverse);
		encoder->SetDistancePerPulse(1.0/442.5);
			// Max speed of the motor without a load is about 116 radians/sec==4424.5 pulses/sec
			// For traction, 0.05027 in/pulse
			// For mecanum, 0.07540 in/pulse
		//encoder->SetMinRate((float) 1/4425.0);
		encoder->SetPIDSourceParameter(encoder->kRate);

		cloop = new PIDController(1.0, 0.5, 0.0, encoder, motor, 0.034);
		cloop->SetInputRange(-1.0, 1.0);
		cloop->SetOutputRange(-10.0, 10.0);

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

public:
	Valve *valve0;
	Valve *valve1;
	
	double maxOutput;
	
	OctocanumDrive();
	void Enable();
	void Disable();
	void Drop();
	void Raise();
	bool GetDriveMode();
	bool GetEnabled();

	void Drive(float x, float y, float rotation);
};

#endif

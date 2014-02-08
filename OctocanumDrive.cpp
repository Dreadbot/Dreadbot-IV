//PLZ DO NOT EDIT THIS, IT WORKS GOODLY
// FIRSST
#include "OctocanumDrive.h"

OctocanumDrive::OctocanumDrive()
{
	for (uint8_t i = 0; i <= 3; i++) 
	{
		drive[i] = new OctocanumModule(i + 1);
		//drive[i]->valve = new Solenoid(i + 1);
	}

	//SmartDashboard::PutBoolean("ODrive.Enabled", false);
	//SmartDashboard::PutBoolean("ODrive.Traction", false);
}

void OctocanumDrive::Enable()
{
	enabled = true;
	SmartDashboard::PutBoolean("ODrive.Enabled", true);
	SmartDashboard::PutBoolean("ODrive.Traction", false);
}

void OctocanumDrive::Disable()
{
	Raise();
	for (uint8_t i = 0; i <= 3; i++) {
		drive[i]->motor->Disable();
	}
	enabled = false;
	SmartDashboard::PutBoolean("ODrive.Enabled", false);
}

void OctocanumDrive::Drop()
{
	if (tractionMode || !enabled) return;
	phaseChange = true;
	for (uint8_t i = 0; i <= 3; i++) {
		drive[i]->motor->Set(0);
	}
	for (uint8_t i = 0; i <= 3; i++) {
		//drive[i]->valve->Set(false);
	}
	Wait(1);// Time that
	tractionMode = true;
	phaseChange = false;
	SmartDashboard::PutBoolean("ODrive.Traction", true);
}

void OctocanumDrive::Raise() 
{
	if (!tractionMode || !enabled) return;
	phaseChange = true;
	for (uint8_t i = 0; i <= 3; i++) {
		//drive[i]->valve->Set(false);
	}
	Wait(1);
	tractionMode = false;
	phaseChange = false;
	SmartDashboard::PutBoolean("ODrive.Traction", false);
}


void OctocanumDrive::MechanumDrive(float x, float y, float rotation, float gyroAngle = 0.0) 
{
	double xIn = x;
	double yIn = -y;
	if (gyroAngle != 0.0) 
	{
		RotateVector(xIn, yIn, gyroAngle);
	}
	double wheelSpeeds[] = {
		xIn + yIn + rotation,
		-xIn + yIn - rotation,
		-xIn + yIn + rotation,
		xIn + yIn - rotation
	};
	Normalize(wheelSpeeds);

	drive[kFrontLeft]->motor->Set(wheelSpeeds[kFrontLeft]);
	drive[kFrontRight]->motor->Set(wheelSpeeds[kFrontRight]);
	drive[kRearLeft]->motor->Set(wheelSpeeds[kRearLeft]);
	drive[kRearRight]->motor->Set(wheelSpeeds[kRearRight]);
}

void OctocanumDrive::ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = false) 
{
	// local variables to hold the computed PWM values for the motors
	float leftMotorOutput;
	float rightMotorOutput;

	moveValue = -Limit(moveValue);
	rotateValue = -Limit(rotateValue);

	if (squaredInputs) 
	{
		if (moveValue >= 0.0) 
		{
			moveValue = (moveValue * moveValue);
		} else {
			moveValue = -(moveValue * moveValue);
		}
		if (rotateValue >= 0.0) 
		{
			rotateValue = (rotateValue * rotateValue);
		} else {
			rotateValue = -(rotateValue * rotateValue);
		}
	}

	if (moveValue > 0.0) {
		if (rotateValue > 0.0) 
		{
			leftMotorOutput = moveValue - rotateValue;
			rightMotorOutput = max(moveValue, rotateValue);
		} else {
			leftMotorOutput = max(moveValue, -rotateValue);
			rightMotorOutput = moveValue + rotateValue;
		}
	} else {
		if (rotateValue > 0.0) 
		{
			leftMotorOutput = -max(-moveValue, rotateValue);
			rightMotorOutput = moveValue + rotateValue;
		} else {
			leftMotorOutput = moveValue - rotateValue;
			rightMotorOutput = -max(-moveValue, -rotateValue);
		}
	}

	SetOutputs(leftMotorOutput, rightMotorOutput);
}

// This is probably the function you were looking for
// Takes the desired x velocity, y velocity, and rotational speed
void OctocanumDrive::Drive(float x, float y, float rotation) 
{
	if (tractionMode) 
	{
		MechanumDrive(x, y, rotation, 0.0);
	} else 
	{
		ArcadeDrive(y, x, true);
	}
}

void OctocanumDrive::SetOutputs(float leftOutput, float rightOutput)
{
	drive[kFrontLeft]->motor->Set(Limit(leftOutput));
	drive[kRearLeft]->motor->Set(Limit(leftOutput));
	drive[kFrontRight]->motor->Set(Limit(rightOutput));
	drive[kRearRight]->motor->Set(Limit(rightOutput));
}

bool OctocanumDrive::GetMode() 
{
	return tractionMode;
}

bool OctocanumDrive::GetEnabled()
{
	return enabled;
}

void OctocanumDrive::Normalize(double *wheelSpeeds)
{
	double maxMagnitude = fabs(wheelSpeeds[0]);
	uint8_t i;
	for (i = 1; i < 4; i++) 
	{
		maxMagnitude = max(maxMagnitude, fabs(wheelSpeeds[i]));
	}
	if (maxMagnitude > 1.0) 
	{
		for (i = 0; i < 4; i++) 
		{
			wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
		}
	}
}

void OctocanumDrive::RotateVector(double &x, double &y, double angle)
{
	angle *= 0.01745329251;
	double cosA = cos(angle);
	double sinA = sin(angle);
	double xOut = x * cosA - y * sinA;
	double yOut = x * sinA + y * cosA;
	x = xOut;
	y = yOut;
}

float OctocanumDrive::Limit(float num) 
{
	if (num > 1.0) 
	{
		return 1.0;
	}
	if (num < -1.0) 
	{
		return -1.0;
	}
	return num;
}

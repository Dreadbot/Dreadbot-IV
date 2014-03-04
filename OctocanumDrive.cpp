#include "OctocanumDrive.h"

OctocanumDrive::OctocanumDrive()
{
	maxOutput = 1.0;

	drive[kFrontLeft] = new OctocanumModule(1, 2, 3, false);
	drive[kFrontRight] = new OctocanumModule(2, 4, 5, false);
	drive[kRearLeft] = new OctocanumModule(3, 6, 7, true);
	drive[kRearRight] = new OctocanumModule(4, 8, 9, false);

	valve0 = new Valve(1, 2);
	valve1 = new Valve(3, 4);
	valve0->Set(true);
	valve1->Set(true);
}

void OctocanumDrive::Enable()
{
	enabled = true;
	for (uint8_t i = 0; i < 3; i++) 
	{
		drive[i]->encoder->Start();
		drive[i]->cloop->Enable();
	}
}

void OctocanumDrive::Disable()
{
	Raise();
	for (uint8_t i = 0; i <= 3; i++) 
	{
		drive[i]->cloop->Disable();
	}
	enabled = false;
}

void OctocanumDrive::Drop()
{
	if (tractionMode || !enabled) return;
	valve0->Set(false);
	valve1->Set(false);
	tractionMode = true;
}

void OctocanumDrive::Raise() 
{
	if (!tractionMode || !enabled) return;
	valve0->Set(true);
	valve1->Set(true);
	tractionMode = false;
}


void OctocanumDrive::MechanumDrive(float x, float y, float rotation)
{
	float xIn = -x;
	float yIn = y;

	wheelSpeeds[kFrontLeft] = xIn + yIn + rotation; 
	wheelSpeeds[kFrontRight] = -xIn + yIn + rotation;
	wheelSpeeds[kRearLeft] = -xIn + yIn - rotation;
	wheelSpeeds[kRearRight] = xIn + yIn - rotation;
}

void OctocanumDrive::ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = false) 
{
	float leftMotorOutput;
	float rightMotorOutput;

	moveValue = Limit(moveValue); 
	rotateValue = Limit(rotateValue);

	if (squaredInputs) 
	{
		if (moveValue >= 0.0) moveValue = (moveValue * moveValue);
		else moveValue = -(moveValue * moveValue);
		
		if (rotateValue >= 0.0)
		{
			rotateValue = (rotateValue * rotateValue);
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

	wheelSpeeds[kFrontLeft] = leftMotorOutput;
	wheelSpeeds[kRearLeft] = leftMotorOutput;
	wheelSpeeds[kFrontRight] = rightMotorOutput;
	wheelSpeeds[kRearRight] = rightMotorOutput;
}


// Drive to <x, y> while rotating
void OctocanumDrive::Drive(float x, float y, float rotation) 
{
	if (!enabled) return;

	if (tractionMode) MechanumDrive(x, y, rotation);
	else ArcadeDrive(x, rotation, true);


	SmartDashboard::PutNumber("FL.PIDIN", wheelSpeeds[kFrontLeft] * maxOutput); // setpoint
	SmartDashboard::PutNumber("FL.MEASURED", drive[kFrontLeft]->encoder->GetRate()); // process variable
	SmartDashboard::PutNumber("FL.PIDOUT", drive[kFrontLeft]->cloop->Get()); // manipulated variable

	SmartDashboard::PutBoolean("ODrive.IsEnabled", enabled);
	SmartDashboard::PutBoolean("ODrive.TractionMode", tractionMode);
	SmartDashboard::PutBoolean("ODrive.IsDancing", dance);
	
	maxOutput = DriverStation::GetInstance()->GetAnalogIn(1);

	Normalize();
	drive[kFrontLeft]->cloop->SetSetpoint(-wheelSpeeds[kFrontLeft] * maxOutput);
	drive[kRearLeft]->cloop->SetSetpoint(-wheelSpeeds[kRearLeft] * maxOutput);
	drive[kFrontRight]->cloop->SetSetpoint(wheelSpeeds[kFrontRight] * maxOutput);
	drive[kRearRight]->cloop->SetSetpoint(wheelSpeeds[kRearRight] * maxOutput);
}

bool OctocanumDrive::GetDriveMode() 
{
	return tractionMode;
}

bool OctocanumDrive::GetEnabled()
{
	return enabled;
}

void OctocanumDrive::Normalize()
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

float OctocanumDrive::Limit(float num) 
{
	if (num > 1.0) 
		return 1.0;
	if (num < -1.0) 
		return -1.0;
	return num;
}

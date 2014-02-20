#include "OctocanumDrive.h"

OctocanumDrive::OctocanumDrive()
{
	maxOutput = 0.5;

	drive[kFrontLeft] = new OctocanumModule(1, 2, 3, true);
	drive[kFrontRight] = new OctocanumModule(2, 4, 5, false);
	drive[kRearLeft] = new OctocanumModule(3, 6, 7, true);
	drive[kRearRight] = new OctocanumModule(4, 8, 9, false);

	valve0 = new Valve(1, 2);
	valve1 = new Valve(3, 4);
}

void OctocanumDrive::Enable()
{
	enabled = true;
	
	for (uint8_t i = 0; i < 4; i++) 
	{
		drive[i]->encoder->Reset();
		drive[i]->encoder->Start();
		drive[i]->speedController->Enable();
	}
	      
	SmartDashboard::PutBoolean("ODrive.Enabled", true);
	SmartDashboard::PutBoolean("ODrive.Traction", false);
}

void OctocanumDrive::Disable()
{
	Raise();
	for (uint8_t i = 0; i < 4; i++) {
		drive[i]->speedController->Disable();
	}
	enabled = false;
	SmartDashboard::PutBoolean("ODrive.Enabled", false);
}

void OctocanumDrive::Drop()
{
	if (tractionMode || !enabled) return;
	valve0->Set(false);
	valve1->Set(false);
	tractionMode = true;
	SmartDashboard::PutBoolean("ODrive.Traction", true);
}

void OctocanumDrive::Raise() 
{
	if (!tractionMode || !enabled) return;
	valve0->Set(true);
	valve1->Set(true);
	tractionMode = false;
	SmartDashboard::PutBoolean("ODrive.Traction", false);
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
	if (tractionMode) MechanumDrive(x, y, rotation);
	else ArcadeDrive(x, rotation, false);

	SmartDashboard::PutNumber("SP_FrontLeft", wheelSpeeds[kFrontLeft]);
	SmartDashboard::PutNumber("SP_FrontRight", wheelSpeeds[kFrontRight]);
	SmartDashboard::PutNumber("SP_RearLeft", wheelSpeeds[kRearLeft]);
	SmartDashboard::PutNumber("SP_RearRight", wheelSpeeds[kRearRight]);

	SmartDashboard::PutNumber("MV_FrontLeft", drive[kFrontLeft]->encoder->PIDGet());
	SmartDashboard::PutNumber("MV_FrontRight", drive[kFrontRight]->encoder->PIDGet());
	SmartDashboard::PutNumber("MV_RearLeft", drive[kRearLeft]->encoder->PIDGet());
	SmartDashboard::PutNumber("MV_RearRight", -drive[kRearRight]->encoder->PIDGet());

	maxOutput = SmartDashboard::GetNumber("Speed");

	#ifdef _PIDTUNE
		for (uint8_t i = 0; i < 4; i++) {
			drive[i]->speedController->SetPID(SmartDashboard::GetNumber("kP"), SmartDashboard::GetNumber("kI"), SmartDashboard::GetNumber("kD"));
		}
	#endif
	
	Set();
}

void OctocanumDrive::Set() {
	Normalize();
	drive[kFrontLeft]->speedController->SetSetpoint(-wheelSpeeds[kFrontLeft] * maxOutput);
	drive[kRearLeft]->speedController->SetSetpoint(-wheelSpeeds[kRearLeft] * maxOutput);
	drive[kFrontRight]->speedController->SetSetpoint(wheelSpeeds[kFrontRight] * maxOutput);
	drive[kRearRight]->speedController->SetSetpoint(wheelSpeeds[kRearRight] * maxOutput);
}

bool OctocanumDrive::GetMode() 
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
		return 1.0;
	if (num < -1.0) 
		return -1.0;
	return num;
}

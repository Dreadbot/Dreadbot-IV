#include "Shooter.h"

Shooter::Shooter(Relay* newMotor, DigitalInput* newSwitch, Solenoid* newSolenoid)
{
	active = true;					//Is the shooter ready to shoot?
	winchAtMax = true;				//Is the winch pulled back yet?
	resetEnabled = false;			//Does the shooter need to be reset?
	winchMotor = newMotor;
	winchSwitch = newSwitch;
	releaser = newSolenoid;
}

void Shooter::shoot()
{
	if (!active) return; //Shooter cannot shoot while not ready
	releaser->Set(false);
	Wait(2.0);
	releaser->Set(true);
	active = false;
	winchAtMax = false;
}

void Shooter::reset()
{
	if (!resetEnabled) return; //Don't reset if resetting isn't allowed
	if (active) return; //Shooter shouldn't reset if it is reset.
	if (winchSwitch->Get()) winchAtMax = true;
	if (!winchAtMax) winchMotor->Set(Relay::kForward);
	if (winchAtMax)
	{
		winchMotor->Set(Relay::kReverse)
		Wait(6.0);
		winchMotor->Set(Relay::kOff);
		active = true;
	}
}

void Shooter::update()
{
	if (resetEnabled) reset();
	if (active) resetEnabled = false;
}

bool Shooter::getActive()
{
	return active;
}

void Shooter::setReset()
{
	resetEnabled = true;
}

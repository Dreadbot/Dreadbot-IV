#include "Shooter.h"

Shooter::Shooter(Talon* newMotor, DigitalInput* newSwitch, Solenoid* newSolenoid)
{
	active = false;
	winchAtMax = false;
	resetEnabled = false;
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
	if (!winchAtMax) winchMotor->Set(1);
	if (winchAtMax)
	{
		winchMotor->Set(-1);
		Wait(4.0);
		winchMotor->Set(0);
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

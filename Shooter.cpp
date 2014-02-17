#include "Shooter.h"

Shooter::Shooter(Talon* newMotor, DigitalInput* newSwitch, Solenoid* newSolenoid)
{
	active = false;
	winchAtMax = false;
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
	if (active) return; //Shooter shouldn't reset if it is reset.
	if (winchSwitch->Get()) winchAtMax;
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
	reset();
}
bool getActive()
{
	return active;
}
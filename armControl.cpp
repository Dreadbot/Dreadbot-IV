#include "armControl.h"

armControl::armControl(Talon* newWheels, Talon* newFlipper, DoubleSolenoid* newArms, Encoder* newPot)
{
	armWheels = newWheels;
	flipper = newFlipper;
	armPneu = newArms;
	flipPot = newPot;
	shooterMode = usrControl;
}
void armControl::moveArms(DoubleSolenoid::Value value)
{
	if (shooterMode != usrControl) return;
	armPneu->Set(value);
}
void armControl::moveWheels(float value)
{
	if (shooterMode != usrControl) return; //Wheels cannot be moved in shootMode
	armWheels->Set(value);
}
void armControl::moveFlipper(float value)
{
	if (shooterMode != usrControl) return; //Flipper cannot be moved in shootMode
	//Possible flipper usage for aiming?
	flipper->Set(value);
}
void armControl::setShootmode(mode newMode)
{
	shooterMode = mode;
}
void armControl::update()
{
	if (shooterMode == usrControl) return; //usrControl doesn't need updating
	if (shooterMode == holding)
	{
		if (flipPot->Get() > FLAPPYUP + ERRVAL)
		{
			flipper->Set(abs(flipPot->Get() - FLAPPYUP) / ERRVAL);
		}
		else if (flipPot->Get() < FLAPPYUP - ERRVAL)
		{
			flipper->Set(abs(flipPot->Get() + FLAPPYUP) / ERRVAL);
		}
	}
}
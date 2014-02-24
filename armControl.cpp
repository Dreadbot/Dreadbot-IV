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
	armPneu->Set(value);
}
void armControl::moveWheels(float value)
{
	armWheels->Set(value);
}
void armControl::moveFlipper(float value)
{
	flipper->Set(value);
}
void armControl::setShootmode(mode newMode)
{
	shooterMode = newMode;
}
int armControl::getFlipPot()
{
	return flipPot->Get();
}

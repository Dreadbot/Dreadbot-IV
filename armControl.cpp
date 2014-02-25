#include "armControl.h"

armControl::armControl(Talon* newWheels, Talon* newFlipper, DoubleSolenoid* newArms, Encoder* newPot)
{
	armWheels = newWheels;
	flipper = newFlipper;
	armPneu = newArms;
	flipPot = newPot;
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
int armControl::getFlipPot()
{
	return flipPot->Get();
}

#include "armControl.h"

ArmControl::ArmControl(Talon* newWheels, Talon* newFlipper, DoubleSolenoid* newArms, AnalogChannel* newPot)
{
	armWheels = newWheels;
	flipper = newFlipper;
	armPneu = newArms;
	flipPot = newPot;
}

void ArmControl::MoveArms(DoubleSolenoid::Value value)
{
	armPneu->Set(value);
}

void ArmControl::MoveWheels(float value)
{
	armWheels->Set(value);
}

void ArmControl::MoveFlipper(float value)
{
	flipper->Set(value);
}

int ArmControl::GetFlipPot()
{
	return flipPot->GetValue();
}

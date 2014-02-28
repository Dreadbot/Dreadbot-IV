#include "armControl.h"

ArmControl::ArmControl(Talon* _wheels, Talon* _flipper, DoubleSolenoid* _arms, Encoder* _pot)
{
	armWheels = _wheels;
	flipper = _flipper;
	armPneu = _arms;
	flipPot = _pot;
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
	return flipPot->Get();
}

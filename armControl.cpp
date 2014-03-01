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
	SmartDashboard::PutNumber("Motor value", value);
	armWheels->Set(value);
}

void ArmControl::MoveFlipper(float value)
{
	/*if (GetFlipPot() > 110 && value > 0) 
	{
		flipper->Set(0.0);
	} else {*/
		flipper->Set(value);
	//}
}

int ArmControl::GetFlipPot()
{
	return flipPot->GetValue() - FLIPPER_OFFSET;
}

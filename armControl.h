#include <WPILib.h>

#define FLIPPER_OFFSET 400

class ArmControl
{
public:
	ArmControl(Talon* newWheels, Talon* newFlipper, DoubleSolenoid* newArms, AnalogChannel* newPot);

	void MoveArms(DoubleSolenoid::Value value);
	void MoveWheels(float value);
	void MoveFlipper(float value);
	int GetFlipPot();

private:
	Talon* armWheels;
	Talon* flipper;
	DoubleSolenoid* armPneu;
	AnalogChannel* flipPot;
};

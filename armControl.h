#include <WPILib.h>


class ArmControl
{
public:
	ArmControl(Talon* _wheels, Talon* _flipper, DoubleSolenoid* _arms, Encoder* _pot);

	void MoveArms(DoubleSolenoid::Value value);
	void MoveWheels(float value);
	void MoveFlipper(float value);

	int GetFlipPot();

private:
	Talon* armWheels;
	Talon* flipper;
	DoubleSolenoid* armPneu;
	Encoder* flipPot;
};

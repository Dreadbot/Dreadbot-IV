#include <WPILib.h>


class armControl
{
public:
	armControl(Talon* newWheels, Talon* newFlipper, DoubleSolenoid* newArms, Encoder* newPot);
	void moveArms(DoubleSolenoid::Value value);
	void moveWheels(float value);
	void moveFlipper(float value);
	int getFlipPot();
private:
	Talon* armWheels;
	Talon* flipper;
	DoubleSolenoid* armPneu;
	Encoder* flipPot;
};

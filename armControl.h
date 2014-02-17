#include <WPILib.h>

class armControl
{
public:
	armControl(Talon* newWheels, Talon* newFlipper, Solenoid* newArms);
	void moveArms(float value);
	void moveWheels(float value);
	void moveFlipper(float value);
	void setShootmode(bool mode);
	void update();
private:
	Talon* armWheels;
	Talon* flipper;
	Solenoid* armPneu;
	bool shootMode;
};
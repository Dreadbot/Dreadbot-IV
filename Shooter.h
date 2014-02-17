#include "WPILib.h"

class Shooter
{
public:
	Shooter(Talon* newMotor, DigitalInput* newSwitch, Solenoid* newSolenoid);
	void shoot();
	void reset();
	void update();
	bool getActive();
private:
	bool active;
	bool winchAtMax;
	Talon* winchMotor;
	DigitalInput* winchSwitch;
	Solenoid* releaser;
};
#include "WPILib.h"

class Shooter
{
public:
	Shooter(Talon* newMotor,
		DigitalInput* newSwitch,
		Solenoid* newSolenoid);
	void shoot();
	void setReset();
	void update();
	bool getActive();
private:
	bool resetEnabled;
	bool active;
	bool winchAtMax;
	Talon* winchMotor;
	DigitalInput* winchSwitch;
	Solenoid* releaser;
	void reset();
};

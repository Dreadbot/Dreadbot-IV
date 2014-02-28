#include "WPILib.h"

class Shooter
{
public:
	Shooter(Relay* newMotor,
		DigitalInput* newSwitch,
		Solenoid* newSolenoid
	);
	
	void shoot();
	void setReset();
	void update();
	
	bool getActive();
	
private:
	void reset();
	
	Relay* winchMotor;
	DigitalInput* winchSwitch;
	Solenoid* releaser;
	
	bool resetEnabled;
	bool active;
	bool winchAtMax;
};

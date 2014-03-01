#include "WPILib.h"
#include "Valve.h"

class Shooter
{
public:
	Shooter(Relay* newMotor,
		DigitalInput* newSwitch,
		Valve* newSolenoid
	);
	
	void shoot();
	void setReset();
	void update();
	
	bool getActive();
	
private:
	void reset();
	
	Relay* winchMotor;
	DigitalInput* winchSwitch;
	Valve* releaser;
	
	bool resetEnabled;
	bool active;
	bool winchAtMax;
};

#include "WPILib.h"

static const int SHOOTPOINT = 100;	//Position at which winch has reset kicker
static const int WINCHSPEED = 1;	//Speed of winch
static const int RESETPOS = 0;		//Winch resting position
static const int WINCHERR = 5;		//Acceptable winch error

class Shooter
{
public:
	Shooter(Talon* _motor, Encoder* _pot);			//Constructor, gets a moter and encoder (pointer)
	void release();									//Shoot the ball!
	void moveTo(double position, int speed = 0);	//Move the shooter arm thingy to the given position. Can be used for autonomous/autoaiming
	bool getActive();								//Is it active?
	void reset();									//Reset the shooter (shift gears again?) for another shot
	void update();									//Iterative function called in main robot class. Allows for pseudo-PID.
private:
	bool active;		//Is it active?
	Talon* winch;		//Motor running winch
	Encoder* pot;		//Encoder attatched to winch
	double position;	//Current position
	bool skip;			//temp bool
};


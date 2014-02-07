#include "WPILib.h"

class Shooter
{
public:
	Shooter(Jaguar* newMotor, Encoder* newPot);
	void release();
	void moveTo(int position, int speed);
	bool getActive();
	bool reset();
	void update();
private:
	bool active;		//Is it active?
	Jaguar* motor;		//Motor running winch
	Encoder* pot;		//Encoder attatched to winch
	int position;		//Current position
	int newPos;			//Position to be moved to 
	int countdown;		//Timer

}

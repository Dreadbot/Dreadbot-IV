#include <WPILib.h>

const int FLAPPYUP = 1000; //STANDIN 
const int FLAPPYDOWN = 0;  //STANDIN
const int ERRVAL = 15;

class armControl
{
public:
	enum mode {holding, usrControl};
	armControl(Talon* newWheels, Talon* newFlipper, DoubleSolenoid* newArms, Encoder* newPot);
	void moveArms(DoubleSolenoid::Value value);
	void moveWheels(float value);
	void moveFlipper(float value);
	void setShootmode(mode newMode);
	void update();
private:
	Talon* armWheels;
	Talon* flipper;
	DoubleSolenoid* armPneu;
	Encoder* flipPot;
	mode shooterMode;
};

#include "armControl.h"

armControl::armControl(Talon* newWheels, Talon* newFlipper, Solenoid* newArms)
{
	armWheels = newWheels;
	flipper = newFlipper;
	armPneu = newArms;
	shootMode = false;
}
void armControl::moveArms(float value)
{
	if (shootMode) return; //Arms cannot be moved in shootMode
	//armPneu->doSomething(value); 
	//Incremental pneumatic control?
}
void armControl::moveWheels(float value)
{
	if (shootMode) return; //Wheels cannot be moved in shootMode
	armWheels->Set(value);
}
void armControl::moveFlipper(float value)
{
	if (shootMode) return; //Flipper cannot be moved in shootMode
	//Possible flipper usage for aiming?
	flipper->Set(value);
}
void armControl::setShootmode(bool mode)
{
	shootMode = mode;
}
void armControl::update()
{
	if (!shootMode) return; //Update unecessary unless
	//shootMode is active

	moveArms(.3); //Move arms to maximum height
	//moveFlipper() Flipper usage or no?
	moveWheels(0); //Stop the wheels from moving
}
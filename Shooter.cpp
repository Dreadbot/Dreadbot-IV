#include "Shooter.h"

Shooter::Shooter(Talon* _motor, Encoder* _pot)
{
	winch = _motor;
	pot = _pot;
}
void Shooter::release()
{
	if (!active) return; //Do NOT release if the shooter is not prepared!
	/* Code for releasing ball. I do not know how to do this.
	Remove latch thingy?
	*/
	active = false;
}
bool Shooter::getActive()
{
	return active;
}
void Shooter::update()
{	
	position = pot->Get();	//Set position equal to encoder position.
	if (!active) reset();
}
void Shooter::reset()
{
	if (position == SHOOTPOINT && !skip)
	{ //If the winch has pulled the kicker back enough
		skip = true;
	}
	else winch->Set(WINCHSPEED);
	if (skip && (position > RESETPOS + WINCHERR || position < RESETPOS - WINCHERR))
	{
		winch->Set(-WINCHSPEED);
	}
	if (position > RESETPOS + WINCHERR || position < RESETPOS -WINCHERR) //Check if winch is reset
	{
		active = true;
		skip = false;
	}
}

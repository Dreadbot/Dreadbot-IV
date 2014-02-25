
#ifndef _VALVE_H_
#define _VALVE_H_

#include "WPILib.h"
class Valve
{
	Solenoid *s0;
	Solenoid *s1;
	bool open;
	
public:
	Valve(uint8_t p_s0, uint8_t p_s1)
	{
		open = false;
		s0 = new Solenoid(p_s0);
		s1 = new Solenoid(p_s1);
	}
	
	bool GetOpen() 
	{
		return open;
	}
	
	void Set(bool v) 
	{
		s1->Set(!v);
		s0->Set(v);
		open = v;
	}
};

#endif

#ifndef VISION_H_
#define VISION_H_

#include "WPILib.h"

class Vision
{
	AxisCamera *camera;
public:
	Vision(DriverStation::Alliance alliance);
	int isHot();
};

#endif

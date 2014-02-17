#include "Vision.h"

#define AREA_MINIMUM 150

Vision::Vision(DriverStation::Alliance alliance)
{
	camera = &AxisCamera::GetInstance();
	ParticleFilterCriteria2 criteria[] = {
			{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
	};
}

int Vision::isHot()
{
	Threshold colorThr(105, 137, 230, 255, 133, 183);
	ColorImage *img = camera->GetImage();
	BinaryImage *thresholdImg = img->ThresholdHSV(colorThr);
	BinaryImage *filterImg = thresholdImg->ParticleFilter(1);
	
	return false;
}

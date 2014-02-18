#ifndef VISION_H_
#define VISION_H_

#include "WPILib.h"
#include <Math.h>

#define Y_IMAGE_RES 480
#define VIEW_ANGLE 49

#define PI 3.141592653

#define RECTANGULARITY_LIMIT 40
#define ASPECT_RATIO_LIMIT 55

#define TAPE_WIDTH_LIMIT 50
#define VERTICAL_SCORE_LIMIT 50
#define LR_SCORE_LIMIT 50

#define AREA_MINIMUM 150

#define MAX_PARTICLES 8

struct TargetReport 
{
	int verticalIndex;
	int horizontalIndex;
	bool Hot;
	double totalScore;
	double leftScore;
	double rightScore;
	double tapeWidthScore;
	double verticalScore;
};

struct Scores 
{
	double rectangularity;
	double aspectRatioVertical;
	double aspectRatioHorizontal;
};

class Vision
{
	AxisCamera *camera;
	double computeDistance (BinaryImage *image, ParticleAnalysisReport *report);
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical);
	double scoreRectangularity(ParticleAnalysisReport *report);
	double ratioToScore(double ratio);
	bool hotOrNot(TargetReport target);
	bool scoreCompare(Scores scores, bool vertical);
public:
	Vision();
	float isHot();
};

#endif

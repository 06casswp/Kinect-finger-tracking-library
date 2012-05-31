#include "handDataSourceSettings.h"

void HandDataSourceSettings::SetToDefault(){
	MinimumDistanceBetweenFingerpoints = 25;
	MinimumDistanceIntersectionpoints = 25;
	MinimumDistanceFingerpointToIntersectionLine = 22;
	MaximumDistanceBetweenIntersectionpoints = 27;

	MaximumRetraceSteps = 128;

	ContourLineThinningDistance = 5.0f;
	MinimalpointsInContour = 50;

	DetectFingers = true;
	DetectCenterOfPalm = true;

	PalmAccuracySearchRadius = 4;
	PalmContourReduction = 8;
}
void HandDataSourceSettings::SetToFast(){
	SetToDefault();
	MaximumRetraceSteps = 50;
	ContourLineThinningDistance = 8.0f;
	PalmAccuracySearchRadius = 2;
	PalmContourReduction = 10;
}

void HandDataSourceSettings::SetToAccurate()        {
	SetToDefault();
	MaximumRetraceSteps = 200;
	ContourLineThinningDistance = 1.0f;
	PalmAccuracySearchRadius = 6;
	PalmContourReduction = 3;
}
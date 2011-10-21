#include "handDataSourceSettings.h"
HandDataSourceSettings::HandDataSourceSettings(){
	SetToDefault();
}
void HandDataSourceSettings::SetToDefault(){
	MinimumDistanceBetweenFingerPoints = 25;
	MinimumDistanceIntersectionPoints = 25;
	MinimumDistanceFingerPointToIntersectionLine = 22;
	MaximumDistanceBetweenIntersectionPoints = 27;

	MaximumRetraceSteps = 128;

	ContourLineThinningDistance = 5.0f;
	MinimalPointsInContour = 50;

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
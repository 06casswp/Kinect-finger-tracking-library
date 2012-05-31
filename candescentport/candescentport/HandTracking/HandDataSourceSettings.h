#ifndef HANDATSRCSET_H
#define HANDATSRCSET_H



class HandDataSourceSettings
{
public:
	

	float MinimumDistanceBetweenFingerpoints;
	float MinimumDistanceIntersectionpoints;
	float MinimumDistanceFingerpointToIntersectionLine;
	float MaximumDistanceBetweenIntersectionpoints;

	float ContourLineThinningDistance;

	bool DetectFingers;

	bool DetectCenterOfPalm;

	int MaximumRetraceSteps;

	int MinimalpointsInContour;

	int PalmAccuracySearchRadius;

	float PalmContourReduction;

	void SetToDefault();
	void SetToFast();

	void SetToAccurate();
};

#endif 
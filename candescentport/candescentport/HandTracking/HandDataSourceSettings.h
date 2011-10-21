#ifndef HANDATSRCSET_H
#define HANDATSRCSET_H



class HandDataSourceSettings
{
public:
	HandDataSourceSettings();

	float MinimumDistanceBetweenFingerPoints;
	float MinimumDistanceIntersectionPoints;
	float MinimumDistanceFingerPointToIntersectionLine;
	float MaximumDistanceBetweenIntersectionPoints;

	float ContourLineThinningDistance;

	bool DetectFingers;

	bool DetectCenterOfPalm;

	int MaximumRetraceSteps;

	int MinimalPointsInContour;

	int PalmAccuracySearchRadius;

	float PalmContourReduction;

	void SetToDefault();
	void SetToFast();

	void SetToAccurate();
};

#endif 
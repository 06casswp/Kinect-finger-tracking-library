#ifndef clusterdatDATSRCSET_H
#define clusterdatDATSRCSET_H
#include "Range.h"

class ClusterDataSourceSettings
{
public:
	int clusterdatCount;
	int LowerBorder;
	int pointModulo;
	int MinimumDepthThreshold;
	int MaximumDepthThreshold;


	rangedat * DepthRange();
	rangedat depth;

	int MinimalpointsForclusterdating;
	int MinimalpointsForValidclusterdat;
	double MergeMinimumDistanceToclusterdat;
	double MergeMaximumclusterdatCenterDistances;
	double MergeMaximumclusterdatCenterDistances2D;
	int MaximumclusterdatDepth;
	void SetToDefault();
	void SetToFast();
	void SetToAccurate();
	



	//new ones
	unsigned short dispoffset; //the distance to include from the saved offset surface
	unsigned short clusterdatcount; //max clusterdats <do not make more than 9>

};



#endif 
#ifndef CLUSTERHELPER_H
#define CLUSTERHELPER_H

//#include "clusterdatasrc.h"
#include "point.h"
#include "clusters.h"

#include "kmeans.h"
#include "clustermerger.h"

class ClusterHelper
{

public:
	ClusterMerger ClusterMergerz;
	KMeans algorithm;

	ClusterDataSourceSettings* settings;
	
	void allocate();

	point** localcopy; //just a local pointer to the pointer array. this is modified only to remove any reduced points by setting their pointer to 0; assigned each update
	int count;

	point* reducedpoints[640*480]; //the new set of working points to be used
	int reducedpointsize;
	point** reduced;
	
	clusterdat clusterdats[10];
	clusterdat *clusterdatpnt[10];
	int localcount;
	clusterdat **clusterdatarray;


	clusterfnc cfnc; //cluster modification functions
	rectfnc rfnc; //rectangle modification functions

	

	clusterdat ** Update();

	bool AreEnoughpointsForclusterdating(int count);


	void Reducepoint();


	void Findclusterdats();

	void FlattenIfRequired(); //will be changed once clusterdats are pointered like points


	void InitializeAlgorithm();



	void AssignAllpoints();

	void MergeclusterdatsIfRequired();



};

#endif 
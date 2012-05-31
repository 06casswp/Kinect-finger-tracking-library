#include "clusterhelper.h"
#include "rectangle.h"
#include "kmeans.h"



void ClusterHelper::allocate() { //rewrite to allocate if not exist, wipe if it does, relies on size and clusterdat count
	int index = 0;
	for (index=0;index<(sizeof(clusterdats)/sizeof(clusterdats[0]));index++) {
		clusterdatpnt[index] = &clusterdats[index];
	}
	clusterdatarray = &clusterdatpnt[0];
	memset(reducedpoints,0,sizeof(reducedpoints));
	reduced = &reducedpoints[0];

}

clusterdat **ClusterHelper::Update(){
	
	reducedpointsize = 0;
	memset(reducedpoints,0,sizeof(reducedpoints)); //reset reduced points before calc

	clusterdatarray = &clusterdatpnt[0];
	
	Reducepoint(); //copies through only relevant points

	if (AreEnoughpointsForclusterdating((int)reducedpointsize)) {
		Findclusterdats();
		if (clusterdatarray == 0) {
			return 0;
		}
		AssignAllpoints();
	}
	else
	{
		return 0;
	}

	
	return clusterdatarray;

}

bool ClusterHelper::AreEnoughpointsForclusterdating(int count){
	return count >= settings->MinimalpointsForclusterdating;

}



void ClusterHelper::Reducepoint(){
	//for statement through localcopy, where the criteria are met and for the corresponding position, add the pointer to reduced points.

	int index;
	int count1 = 0;
	int mod = settings->pointModulo;
	
	for (index=0;index<count;index++) {
		if (!(localcopy[index]==0)) {
			count1++;
			if (((int)localcopy[index]->x % mod == 0) && ((int)localcopy[index]->y % mod == 0)) {
				reducedpoints[reducedpointsize] = localcopy[index]; //assign pointer to reduced array
				reducedpointsize++;
			}
		}
	}
	//printf("\n original count: %d", count1);
}

void ClusterHelper::Findclusterdats(){ //this uses reduced list
	algorithm.setclustcount = settings->clusterdatcount;
	algorithm.reducedcount = reducedpointsize;
	algorithm.IterateUntilStable();

	if (algorithm.clusterdatcount > 0)
	{

		MergeclusterdatsIfRequired();
		FlattenIfRequired();
		//flatten, then no return, just leave in the array with the correct count
		//printf("\nclusterdat Data Generated");
	}
	else
	{

		clusterdatarray = 0;
	}
} 


void ClusterHelper::FlattenIfRequired(){
	int index = 0;
	if (settings->MaximumclusterdatDepth)
	{
		for (index = 0; index<localcount;index++) {
			cfnc.Flatten(clusterdatpnt[index], settings->MaximumclusterdatDepth);
		}
	}	
}






void ClusterHelper::AssignAllpoints(){ //takes fulllist (non reduced) (localcopy)
	int index = 0;
	int index1 = 0;
	
	rectdata rect;
	

	for (index = 0;index<2; index++) { //modify this to change cluster count
	clusterdatarray[index]->allpointscnt = 0;
	clusterdatarray[index]->allpointpnt = &clusterdatarray[index]->Allpoints[0];
		for (index1=0;index1<count;index1++) {
			cfnc.Area(&rect,clusterdatarray[index]);
			if (rfnc.Contains(&rect, localcopy[index1])) {
				clusterdatarray[index]->Allpoints[clusterdatarray[index]->allpointscnt] = localcopy[index1];
				clusterdatarray[index]->allpointscnt++;
			}
		}
	}

	//printf("\nAssigned all points to their classes");
	
}

void ClusterHelper::MergeclusterdatsIfRequired(){
	int index = 0;
	clusterdat *localclusterdats[10];
	clusterdat **localpnt;
	localpnt = &localclusterdats[0];
	localcount = 0;
	for (index=0;index<2;index++) {
		if (clusterdatarray[index]->pointscnt>settings->MinimalpointsForValidclusterdat) {//using reduced count
			cfnc.CalculateVolume(clusterdatarray[index]);
			localclusterdats[localcount] = clusterdatarray[index];
			localcount++;
		}
	}
	if (localcount > 1) {
		int clustcount = localcount;
		do
		{
			clustcount = localcount;
			ClusterMergerz.MergeclusterdatsIfRequired(localpnt, &clustcount);
		}
		while (clustcount != localcount);
	}
	printf("\n%d\n", localcount);


}
#include "clusterdata.h"


ClusterData::ClusterData(std::vector<Cluster*>* clusters)
{
	Clusters = clusters;
}

int ClusterData::Count(){
	return Clusters->size();


}

ClusterData::ClusterData(){
	Clusters = new std::vector<Cluster*>;

}
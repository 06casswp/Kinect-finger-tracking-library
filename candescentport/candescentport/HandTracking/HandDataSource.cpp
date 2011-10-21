#include "HandDataSource.h"
#include "HandDataFactory.h"
#include "DistanceMap2.h"


HandDataSource::HandDataSource(IClusterDataSource *clusterDataSource) : DataSourceProcessor(clusterDataSource)
{
	
	factory = new HandDataFactory(new HandDataSourceSettings());
	size = clusterDataSource->Size;
	CurrentValue = new HandCollection();

}

HandDataSource::HandDataSource(IClusterDataSource* clusterDataSource, HandDataSourceSettings* settings) : DataSourceProcessor(clusterDataSource)
{

	factory = new HandDataFactory(settings);
	size = clusterDataSource->Size;
	CurrentValue = new HandCollection();

}





HandCollection* HandDataSource::Process(ClusterData clusterData1){
	if (clusterData1.Count() == 0)
	{
		factory->ClearIds();
		return new HandCollection();
	}

	DistanceMap2<HandData*, Cluster*>* map = new DistanceMap2<HandData*, Cluster*>(CurrentValue->Hands, 100); //TODO
	map->Map(clusterData1.Clusters);

	std::vector<HandData*>* result = new std::vector<HandData*>;
	std::vector<HandData*>::iterator iter1;
	std::vector<Cluster*>::iterator iter2;
	std::vector<std::tuple<HandData*,Cluster*>>::iterator iter3;
	Cluster * cl;
	HandData* hd;
	std::tuple<HandData*,Cluster*>;
	/*
	for (iter3 = map->MappedItems->begin();iter3<map->MappedItems->end();iter3++)
	{
		tupple = *iter3;
		//result->push_back(factory->Create(tupple->Item1, tupple.Item2));
	}
	*/
	for (iter2=map->UnmappedItems->begin();iter2<map->UnmappedItems->end();iter2++)
	{
		cl = (Cluster*)*iter2;
		result->push_back(factory->Create(cl));
	}
	for (iter1=map->DiscontinuedItems->begin();iter1<map->DiscontinuedItems->end();iter1++) {
	
		hd = (HandData*)*iter1;
		factory->ReturnId(hd->id);
	}
	
	return new HandCollection(result);
}



	int HandDataSource::Width(){
		return size->Width;
	}


	int HandDataSource::Height(){
		return size->Height;
	}
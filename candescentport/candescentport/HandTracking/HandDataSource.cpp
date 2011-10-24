#include "HandDataSource.h"
#include "HandDataFactory.h"
#include "DistanceMap2.h"
#include "../clusterdatasrc.h"


HandDataSource::HandDataSource(ClusterDataSource *clusterDataSource)// : DataSourceProcessor(clusterDataSource)
{
	
	factory = new HandDataFactory(new HandDataSourceSettings());
	Size = clusterDataSource->Size;
	CurrentValue = new HandCollection();

}

HandDataSource::HandDataSource(intsize* size1,/*ClusterDataSource* clusterDataSource,*/ HandDataSourceSettings* settings) //: DataSourceProcessor(clusterDataSource)
{

	factory = new HandDataFactory(settings);
	Size = size1;//clusterDataSource->Size;
	CurrentValue = new HandCollection();

}





HandCollection* HandDataSource::Process(ClusterData* clusterData1){
	if (clusterData1->Count() == 0)
	{
		factory->ClearIds();
		return new HandCollection();
	}
	CurrentValue = new HandCollection();
	CurrentValue->Hands = new std::vector<HandData*>;
	DistanceMap2a* map = new DistanceMap2a(CurrentValue->Hands, 100); //TODO
	map->Map(clusterData1->Clusters);

	
	std::vector<HandData*>* result = new std::vector<HandData*>;
	std::vector<HandData*>::iterator iter1;
	std::vector<Cluster*>::iterator iter2;
	std::vector<std::tr1::tuple<HandData*,Cluster*>*>::iterator iter3;
	Cluster * cl;
	HandData* hd;
	std::tr1::tuple<HandData*,Cluster*>* tupple;
	
	for (iter3 = map->MappedItems->begin();iter3<map->MappedItems->end();iter3++)
	{
		tupple = (std::tr1::tuple<HandData*,Cluster*>*)*iter3;
		result->push_back(factory->Create(std::get<0>(*tupple), std::get<1>(*tupple)));
	}
	
	for (iter2=map->UnmappedItems->begin();iter2<map->UnmappedItems->end();iter2++)
	{
		cl = (Cluster*)*iter2;
		result->push_back(factory->Create(new Cluster((void*)cl)));
	}
	for (iter1=map->DiscontinuedItems->begin();iter1<map->DiscontinuedItems->end();iter1++) {
	
		hd = (HandData*)*iter1;
		factory->ReturnId(hd->id);
	}
	
	return new HandCollection(result);
}



	int HandDataSource::Width(){
		return Size->Width;
	}


	int HandDataSource::Height(){
		return Size->Height;
	}
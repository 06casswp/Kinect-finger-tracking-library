#include "clusterdatasrc.h"
#include "clusterhelper.h"
#include "datasourceprocessor.h"



	ClusterDataSource::ClusterDataSource(IDepthPointerDataSource* dataSource1, ClusterDataSourceSettings* settings1): DataSourceProcessor<ClusterData*,int*>(dataSource1){
		settings = settings1;
		size = dataSource1->Size;
		data = new ClusterData();
		clusterHelper = new ClusterHelper(settings, size);


}

ClusterDataSource::ClusterDataSource(IDepthPointerDataSource* dataSource1):DataSourceProcessor(dataSource1){

		settings = new  ClusterDataSourceSettings();
		size = dataSource1->Size;
		data = new ClusterData();
		clusterHelper = new ClusterHelper(settings, size);

}

ClusterData* ClusterDataSource::Process(const XnDepthPixel * sourceData)
{
	ClusterHelper *clusterh = (ClusterHelper *)clusterHelper;
	return clusterh->Update(FindPointsWithinDepthRange(sourceData));
}


std::vector<Point*>* ClusterDataSource::FindPointsWithinDepthRange(const XnDepthPixel * dataPointer)
{
	std::vector<Point*>* result = new std::vector<Point*>;
	Point* p1;
	XnUInt16* pDepth = (XnUInt16*)dataPointer;

	int localHeight = size->Height; //5ms faster when it's a local variable
	int localWidth = size->Width;
	int maxY = localHeight - settings->LowerBorder;
	int minDepth = settings->MinimumDepthThreshold;
	int maxDepth = settings->MaximumDepthThreshold;

	for (int y = 0; y < localHeight; y++)
	{
		for (int x = 0; x < localWidth; x++)
		{
			XnUInt16 depthValue = *pDepth;
			if (depthValue > 0 && y < maxY && depthValue <= maxDepth && depthValue >= minDepth) //Should not be put in a seperate method for performance reasons
			{
				p1 = new Point(x, y, depthValue);
				result->push_back(p1);
			}
			pDepth++;
		}
	}
	return result;
}
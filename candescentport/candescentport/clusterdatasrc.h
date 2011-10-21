#ifndef CLUSTERDATSRC_H
#define CLUSTERDATSRC_H


#include "clusterdatasrcsets.h"
#include "intsize.h"

#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "iclusterdatasrc.h"
#include "idepthpntdatsource.h"
#include "datasourceprocessor.h"




class ClusterDataSource : public DataSourceProcessor<ClusterData*, int*>, public IClusterDataSource
{
public:
	ClusterDataSourceSettings* settings;
	intsize* size;
	void* clusterHelper;
	ClusterDataSource(IDepthPointerDataSource* dataSource, ClusterDataSourceSettings* settings);
	ClusterDataSource(IDepthPointerDataSource* dataSource);
	ClusterData* Process(const XnDepthPixel * sourceData);
	std::vector<Point*>* FindPointsWithinDepthRange(const XnDepthPixel * dataPointer);
	int width();
	int height();

};

#endif 

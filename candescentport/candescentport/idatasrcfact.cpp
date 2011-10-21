#include "idatasrcfact.h"


IDataSourceFactory::IDataSourceFactory(){
	openni = new OpenNIDataSourceFactory("config.xml");
	rgbimagesrc = openni->CreateRGBImageDataSource();
	depthimagesrc = openni->CreateDepthImageDataSource();
	iclustersrc = openni->CreateClusterDataSource();


}
IDataSourceFactory::IDataSourceFactory(ClusterDataSourceSettings* clusterDataSourceSettings){
	rgbimagesrc = openni->CreateRGBImageDataSource();
	depthimagesrc = openni->CreateDepthImageDataSource();
	iclustersrc = openni->CreateClusterDataSource(clusterDataSourceSettings);

}
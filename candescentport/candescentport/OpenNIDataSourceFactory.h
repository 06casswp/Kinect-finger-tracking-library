#ifndef OPENNIDATSRCFAC_H
#define OPENNIDATSRCFAC_H

#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "clusterdatasrcsets.h"
#include "iclusterdatasrc.h"
#include "Iimagesource.h"
#include <string>
#include "idepthpntdatsource.h"
#include "irgbpntdatsrc.h"
#include "clusterdatasrc.h"
#include "depthpntdatsrc.h"
#include "rgbpntdatsrc.h"
#include "idatasrcfact.h"



class OpenNIDataSourceFactory //: public IDataSourceFactory
{
public:
	xn::Context context;
	DepthPointerDataSource* depthPointerDataSource;
	IRGBPointerDataSource* rgbPointerDataSource;
	DepthPointerDataSource* idpds;
	OpenNIDataSourceFactory(std::string configFile);
	xn::DepthGenerator depthgen;

	xn::DepthGenerator* GetDepthGenerator();

	xn::ImageGenerator* GetImageGenerator();

	IImageSource CreateRGBImageDataSource();

	IImageSource CreateDepthImageDataSource();

	IClusterDataSource* CreateClusterDataSource(ClusterDataSourceSettings* clusterDataSourceSettings);
	ClusterDataSource* CreateClusterDataSource1(ClusterDataSourceSettings* clusterDataSourceSettings);
	ClusterDataSource* CreateClusterDataSource1();
	IClusterDataSource* CreateClusterDataSource();

	DepthPointerDataSource* GetDepthPointerDataSource();

	IRGBPointerDataSource GetRGBPointerDataSource();

	void DisposeAll();
};


#endif 
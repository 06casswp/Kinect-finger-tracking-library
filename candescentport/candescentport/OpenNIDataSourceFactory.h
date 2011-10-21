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



class OpenNIDataSourceFactory
{
public:
	xn::Context context;
	IDepthPointerDataSource* depthPointerDataSource;
	IRGBPointerDataSource* rgbPointerDataSource;

	OpenNIDataSourceFactory(std::string configFile);


	xn::DepthGenerator GetDepthGenerator();

	xn::ImageGenerator GetImageGenerator();

	IImageSource* CreateRGBImageDataSource();

	IImageSource* CreateDepthImageDataSource();

	IClusterDataSource* CreateClusterDataSource(ClusterDataSourceSettings* clusterDataSourceSettings);

	IClusterDataSource* CreateClusterDataSource();

	IDepthPointerDataSource* GetDepthPointerDataSource();

	IRGBPointerDataSource* GetRGBPointerDataSource();

	void DisposeAll();
};


#endif 
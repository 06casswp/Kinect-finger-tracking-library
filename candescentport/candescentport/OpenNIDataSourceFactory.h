#ifndef OPENNIDATSRCFAC_H
#define OPENNIDATSRCFAC_H

#include <XnCppWrapper.h>
#include "clusterdatasrcsets.h"
#include "iclusterdatasrc.h"
#include "Iimagesource.h"
#include <string>
#include "idepthpntdatsource.h"
#include "irgbpntdatsrc.h"
#include "clusterdatasrc.h"
#include "depthpntdatsrc.h"
#include "rgbpntdatsrc.h"

#include "clusterhelper.h"



class OpenNIDataSourceFactory 
{
public:
	xn::Context context;
	DepthpointerDataSource* depthpointerDataSource;
	IRGBpointerDataSource* rgbpointerDataSource;
	DepthpointerDataSource* idpds;

	ClusterDataSource cd;
	ClusterHelper ch;
	ClusterDataSourceSettings settings;
	xn::ImageGenerator imagegen;
	xn::DepthGenerator depthgen;
	xn::DepthMetaData metaDat;
	xn::ScriptNode node;
	XnStatus _rc;
	bool init(std::string configFile);


	
	ClusterDataSource* CreateClusterDataSource1();

	

	void DisposeAll();
};


#endif 
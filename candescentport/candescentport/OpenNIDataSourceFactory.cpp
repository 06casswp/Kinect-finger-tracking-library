
#include "OpenNIDataSourceFactory.h"
#include <iostream>
#include <fstream>


bool OpenNIDataSourceFactory::init(std::string configFile) {


	
	bool flag = false;
	std::fstream fin;
	fin.open("config.xml",std::ios::in);
	if( fin.is_open() )
	{
		flag = true;

	}
	fin.close();
	if (flag) {
		_rc = context.Init();//InitFromXmlFile((const XnChar*)configFile.c_str(),node, 0);
			printf("\n%s",xnGetStatusString(_rc));
		if (!(_rc==0)) {
			printf("\nFailed to Initialise OpenNI context - %s, did you remember to plug it in? try changing ports", xnGetStatusString(_rc));
			return 0;
		}
		else
		{
			printf("\nInitialised OpenNI context");
			_rc = depthgen.Create(context);
			if (!(_rc==0)) {
				printf("\nDepth gen init failed: %s, did you remember the kinect power cable",xnGetStatusString(_rc));
				return 0;
			}
			else
			{
				printf("\nInitialised depth data image");
			}
			return 1;
		}

	}
}

ClusterDataSource* OpenNIDataSourceFactory::CreateClusterDataSource1()
{
	idpds = new DepthpointerDataSource(&depthgen);//this is only used for size??
	settings.SetToDefault();
	cd.settings = &settings; //set size and settings
	cd.size = &idpds->Size;

		cd.clusterhelper = &ch;
		ch.ClusterMergerz.settings = &settings;
		ch.settings = &settings;
		ch.allocate();
		ch.algorithm.setclustcount = settings.clusterdatCount;
		ch.algorithm.reducedpoints = ch.reduced;
		ch.algorithm.size = cd.size;
		ch.algorithm.zrangedat = settings.DepthRange();
		ch.algorithm.clusterdatarr = ch.clusterdatarray;
	//printf("\nCreated clusterdat Data Source");
	return &cd;
}




void OpenNIDataSourceFactory::DisposeAll()
{
	OpenNIDataSourceFactory::context.Release();
}
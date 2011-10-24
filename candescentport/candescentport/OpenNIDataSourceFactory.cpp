
#include "OpenNIDataSourceFactory.h"
#include "rgbimagesrc.h"
#include "depthimagesource.h"
#include <iostream>
#include <fstream>


OpenNIDataSourceFactory::OpenNIDataSourceFactory(std::string configFile){
	/*
	//check if config file exists
	if (!File.Exists(configFile))
	{
	throw new FileNotFoundException("Config file is missing: " + configFile);
	}
	*/
	xn::ScriptNode node;
	bool flag = false;
std::fstream fin;
fin.open("config.xml",std::ios::in);
if( fin.is_open() )
{
	flag = true;

}
fin.close();
if (flag) {
//XnStatus _rc = OpenNIDataSourceFactory::context.InitFromXmlFile((const XnChar*)configFile.c_str(),node, 0);
printf("\nInitialising OpenNI context");	
}
//xn::DepthGenerator depth;
XnStatus nRetVal = context.Init();
//printf("");
	//CHECK_RC(nRetVal, "Initialize context");
	// Create the depth object
	nRetVal = depthgen.Create(context);
	//CHECK_RC(nRetVal, "Create Depth");
	xn::DepthMetaData metaDat;
	//depthgen.GetMetaData(metaDat);
	//printf("%d,%d",metaDat.XRes(),metaDat.YRes());
	


}


xn::DepthGenerator* OpenNIDataSourceFactory::GetDepthGenerator(){


	    XnStatus _rc = context.FindExistingNode(XN_NODE_TYPE_DEPTH, depthgen);
        if(_rc != XN_STATUS_OK)
        {       // could not find the depth, create it by default

                _rc = depthgen.Create(context);
        }
	
		bool check = depthgen.IsValid();
		//printf("");
			xn::DepthMetaData metaDat;
	depthgen.GetMetaData(metaDat);
	printf("\nReceived size of depth data Res:%d,%d",metaDat.XRes(),metaDat.YRes());

	//context.StartGeneratingAll();
	return 0;


}

xn::ImageGenerator* OpenNIDataSourceFactory::GetImageGenerator(){
	xn::ImageGenerator found;
	OpenNIDataSourceFactory::context.FindExistingNode(XN_NODE_TYPE_IMAGE,found);

	return &found;

}

IImageSource OpenNIDataSourceFactory::CreateRGBImageDataSource(){
	IImageSource em = RGBImageSource(&GetRGBPointerDataSource());
	return em;
}

IImageSource OpenNIDataSourceFactory::CreateDepthImageDataSource(){
	IImageSource em = DepthImageSource(GetDepthPointerDataSource());
	return em;

}

IClusterDataSource* OpenNIDataSourceFactory::CreateClusterDataSource(ClusterDataSourceSettings* clusterDataSourceSettings)
{
	IDepthPointerDataSource* idpds = GetDepthPointerDataSource();

	IClusterDataSource *cds = new ClusterDataSource(idpds->Size, clusterDataSourceSettings);
	printf("\nCreated Cluster Data Source");
	return cds;
}
ClusterDataSource* OpenNIDataSourceFactory::CreateClusterDataSource1(ClusterDataSourceSettings* clusterDataSourceSettings)
{
	idpds = GetDepthPointerDataSource();

	ClusterDataSource* cds = new ClusterDataSource(idpds->Size, clusterDataSourceSettings);
	printf("\nCreated Cluster Data Source");
	return cds;
}

IClusterDataSource* OpenNIDataSourceFactory::CreateClusterDataSource()
{
	return CreateClusterDataSource(new ClusterDataSourceSettings());
}

ClusterDataSource* OpenNIDataSourceFactory::CreateClusterDataSource1()
{
	return CreateClusterDataSource1(new ClusterDataSourceSettings());
}

DepthPointerDataSource* OpenNIDataSourceFactory::GetDepthPointerDataSource()
{
	//GetDepthGenerator();

	bool check = depthgen.IsValid();
	depthPointerDataSource = new DepthPointerDataSource(&depthgen);

	return depthPointerDataSource;
}

IRGBPointerDataSource OpenNIDataSourceFactory::GetRGBPointerDataSource()
{

	//IRGBPointerDataSource* rgbPointerDataSource = (IRGBPointerDataSource*)&

	return RGBPointerDataSource(OpenNIDataSourceFactory::GetImageGenerator());
}

void OpenNIDataSourceFactory::DisposeAll()
{
	OpenNIDataSourceFactory::context.Release();
}
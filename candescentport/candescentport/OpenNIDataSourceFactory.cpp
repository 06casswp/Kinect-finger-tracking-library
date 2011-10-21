
#include "OpenNIDataSourceFactory.h"
#include "rgbimagesrc.h"
#include "depthimagesource.h"


OpenNIDataSourceFactory::OpenNIDataSourceFactory(std::string configFile){
	/*
	//check if config file exists
	if (!File.Exists(configFile))
	{
	throw new FileNotFoundException("Config file is missing: " + configFile);
	}
	*/

	xn::ScriptNode node;


	OpenNIDataSourceFactory::context.InitFromXmlFile((const XnChar*)configFile.c_str(),node, 0);


}


xn::DepthGenerator OpenNIDataSourceFactory::GetDepthGenerator(){
	xn::DepthGenerator found;
	OpenNIDataSourceFactory::context.FindExistingNode(XN_NODE_TYPE_DEPTH,found);
	return found;


}

xn::ImageGenerator OpenNIDataSourceFactory::GetImageGenerator(){
	xn::DepthGenerator found;
	OpenNIDataSourceFactory::context.FindExistingNode(XN_NODE_TYPE_IMAGE,found);

	return found;

}

IImageSource* OpenNIDataSourceFactory::CreateRGBImageDataSource(){
	IImageSource* em = &RGBImageSource(GetRGBPointerDataSource());
	return em;
}

IImageSource* OpenNIDataSourceFactory::CreateDepthImageDataSource(){
	IImageSource* em = &DepthImageSource(GetDepthPointerDataSource());
	return em;

}

IClusterDataSource* OpenNIDataSourceFactory::CreateClusterDataSource(ClusterDataSourceSettings* clusterDataSourceSettings)
{
	return &ClusterDataSource(GetDepthPointerDataSource(), clusterDataSourceSettings);
}

IClusterDataSource* OpenNIDataSourceFactory::CreateClusterDataSource()
{
	return CreateClusterDataSource(&ClusterDataSourceSettings());
}

IDepthPointerDataSource* OpenNIDataSourceFactory::GetDepthPointerDataSource()
{

	IDepthPointerDataSource* depthPointerDataSource = (IDepthPointerDataSource*)&DepthPointerDataSource(OpenNIDataSourceFactory::GetDepthGenerator());

	return depthPointerDataSource;
}

IRGBPointerDataSource *OpenNIDataSourceFactory::GetRGBPointerDataSource()
{

	IRGBPointerDataSource* rgbPointerDataSource = (IRGBPointerDataSource*)&RGBPointerDataSource(OpenNIDataSourceFactory::GetImageGenerator());

	return rgbPointerDataSource;
}

void OpenNIDataSourceFactory::DisposeAll()
{
	OpenNIDataSourceFactory::context.Release();
}

#include "main.h"


void main() {
	printf("\nProgram Start");
	program *pro = new program;
    pro->factory = pro->CreateFactory();
	pro->CreateDataSources();
	//has a start function, then it has a callback function on newdataavailable
	//start generating
	printf("\nOpenNI starting Generating");
	pro->factory->context.StartGeneratingAll();


	while(1) {
		//wait for
		pro->factory->context.WaitOneUpdateAll(pro->factory->depthgen);
		//pass to cluster
		printf("\nGenerating Clusters");
		ClusterData *cd = pro->clustersource->Process(pro->factory->depthgen.GetDepthMap(),pro->other);
		//pass cluster to hand
		printf("\nOutputing Clusters to Image");
		if (cd->Clusters->size()>0) {
		intarray2bmp::intarray2bmp <unsigned __int16> ( "cluster1.bmp", cd->Clusters->at(0), (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );
		}
		if (cd->Clusters->size()>1) {
		intarray2bmp::intarray2bmp <unsigned __int16> ( "cluster2.bmp", cd->Clusters->at(1), (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );
		}
		printf("\nGenerating Hand Data");
		HandCollection* HC = pro->handDataSource->Process(cd);
		printf("\nHands Found: %d",HC->Count());
	}


	return;
}

OpenNIDataSourceFactory* program::CreateFactory(){
	return new OpenNIDataSourceFactory("Config.xml");
}

void program::CreateDataSources()
        {
			printf("\nCreating Data Sources");
            HandDataSourceSettings settings;
            //settings.DetectCenterOfPalm = false; //Not used, so disabling this makes the app faster
			clustersource = factory->CreateClusterDataSource1();
			other = clustersource->clusterHelper;

			intsize size = *clustersource->size;
            handDataSource = new HandDataSource(&size,/*clustersource,*/ &settings);
			
            //handDataSource->NewDataAvailable += new NewDataHandler<HandCollection>(handDataSource_NewDataAvailable);
            //handDataSource->Start();
        }

	program::program() {
		minNumberOfFingersToShowMenu = 4;

	}
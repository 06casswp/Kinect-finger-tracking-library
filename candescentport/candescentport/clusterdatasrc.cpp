#include "clusterdatasrc.h"
#include "clusterhelper.h"
#include "datasourceprocessor.h"



	ClusterDataSource::ClusterDataSource(intsize* size1, ClusterDataSourceSettings* settings1)//: DataSourceProcessor<ClusterData*,const XnDepthPixel *>(){
	{
		settings = settings1;
		size = size1;
		data = new ClusterData();
		clusterHelper = new ClusterHelper(settings, size1);
		printf("\nCluster Data Source Created");

}

ClusterDataSource::ClusterDataSource(IDepthPointerDataSource* dataSource1)//:DataSourceProcessor(dataSource1){
{
		settings = new ClusterDataSourceSettings();
		//Size = dataSource1->Size;
		data = new ClusterData();
		clusterHelper = new ClusterHelper(settings, Size);
		printf("\nCluster Data Source Created");
}

ClusterData* ClusterDataSource::Process(const XnDepthPixel * sourceData, void* other)
{
	ClusterHelper *clu = (ClusterHelper*)other;
	printf("\nProcessing depth data");
	pin = FindPointsWithinDepthRange(sourceData);
	clu->localcpy = new std::vector<Point*>;
	std::vector<Point*>::iterator iter;
	clu->localcpy->empty();
	for (iter=result.begin();iter<result.end();iter++) {
		clu->localcpy->push_back((Point*)*iter);
	}
	return clu->Update();
}


std::vector<Point*>* ClusterDataSource::FindPointsWithinDepthRange(const XnDepthPixel * dataPointer)
{
	intarray2bmp1::intarray2bmp1 <unsigned __int16> ( "depthimage.bmp", (unsigned __int16*)dataPointer, (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );

	//result = new std::vector<Point*>;
	result.clear();
	XnUInt16* pDepth = (XnUInt16*)dataPointer;
	printf("\nGetting Point Data from depth image",test);
	int localHeight = size->Height; //5ms faster when it's a local variable
	int localWidth = size->Width;
	int maxY = localHeight - settings->LowerBorder;
	int minDepth = settings->MinimumDepthThreshold;
	int maxDepth = settings->MaximumDepthThreshold;
	int y,x;
	for (y = 0; y < localHeight-1; y++)
	{
		for (x = 0; x < localWidth-1; x++)
		{
			XnUInt16 depthValue = pDepth[(640*480-1)-(640*y+x)];
			if (depthValue > 0 && y < maxY && depthValue <= maxDepth && depthValue >= minDepth) //Should not be put in a seperate method for performance reasons
			{
				p1 = new Point(x, y, depthValue);
				result.push_back(p1);
			}
			
		}
	}
	//printf("lastx: %d, lasty: %d last: %d",x,y, 640*y+x);
	printf("\nFiltered input data, outputting point image");
	intarray2bmp ( "points1.bmp", (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );
	return &result;
}

  char Adjust1(double color, double factor){
	  double Gamma = 0.80;
	  double IntensityMax = 255;
	  if (color == 0) {
		  return 0;
	  }
	  else
	  {
		  return (IntensityMax*pow(color*factor,Gamma));
	  }
  }


  void WavelengthToRGB1(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B) {

	  double Gamma        =   0.80;
	  double IntensityMax = 255;
	  double Blue = 0;
	  double factor = 0;
	  double Green = 0;
	  double Red = 0;


	  if ((wavelength>=380)& (wavelength<=439)) {

		  Red   = -(wavelength - 440) / (440 - 380);
		  Green = 0.0;
		  Blue  = 1.0;
	  }
	  if ((wavelength>=440)& (wavelength<=489)) {

		  Red   = 0.0;
		  Green = (wavelength - 440) / (490 - 440);
		  Blue  = 1.0;
	  }
	  if ((wavelength>=490)& (wavelength<=509)) {

		  Red   = 0.0;
		  Green = 1.0;
		  Blue  = -(wavelength - 510) / (510 - 490);
	  }
	  if ((wavelength>=510)& (wavelength<=579)) {

		  Red   = (wavelength - 510) / (580 - 510);
		  Green = 1.0;
		  Blue  = 0.0;
	  }
	  if ((wavelength>=580)& (wavelength<=644)) {

		  Red   = 1.0;
		  Green = -(wavelength - 645) / (645 - 580);
		  Blue  = 0.0;
	  }
	  if ((wavelength>=645)& (wavelength<=780)) {

		  Red   = 1.0;
		  Green = 0.0;
		  Blue  = 0.0;
	  }
	  if ((wavelength>781)& (wavelength<380)) {
		  Red  = 0.0;
		  Green = 0.0;
		  Blue  = 0.0;
	  }



	  // Let the intensity fall off near the vision limits

	  if ((wavelength>=380)& (wavelength<=419)) {  
		  factor = 0.3 + 0.7*(wavelength - 380) / (420 - 380);
	  }
		  if ((wavelength>=420)& (wavelength<=700)) {  
			  factor = 1.0;
		  }
		  if ((wavelength>=701)& (wavelength<=780)) {  
			  factor = 0.3 + 0.7*(780 - wavelength) / (780 - 700);
		  }
		  if ((wavelength<380)& (wavelength>780)) { 
			  factor = 0.0;
		  }



  *R = Adjust1(Red,   factor);
  *G = Adjust1(Green, factor);
  *B = Adjust1(Blue,  factor);
	  }
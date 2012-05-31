#include "clusterdatasrc.h"
#include "clusterhelper.h"
#include "datasourceprocessor.h"





		
	



clusterdat ** ClusterDataSource::Process(const XnDepthPixel * sourceData, point *p1, point *poff, point ** filtered)
{
	filteredarray = filtered;
	ClusterHelper *clu = (ClusterHelper*)clusterhelper;
	//printf("\nProcessing depth data");
	FindpointsWithinDepthRange(sourceData,p1,poff); //results in a valid depth image in filtered
	
	clu->localcopy = filteredarray; //send through the original filtered to clu->localcpy
	clu->count = count;

	clusterdat** result = clu->Update();
	found = clu->localcount;
	return result;
}


void ClusterDataSource::FindpointsWithinDepthRange(const XnDepthPixel * datapointer, point *p1, point *poff)
{
	//intarray2bmp1::intarray2bmp1 <unsigned __int16> ( "depthimage.bmp", (unsigned __int16*)datapointer, (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );


	XnUInt16* pDepth = (XnUInt16*)datapointer;
	//printf("\nGetting point Data from depth image");
	int localHeight = size->Height; //5ms faster when it's a local variable
	int localWidth = size->Width;
	int maxY = localHeight - settings->LowerBorder;
	int minDepth = settings->MinimumDepthThreshold;
	int maxDepth = settings->MaximumDepthThreshold;
	int y,x;
	XnUInt16 depthValue;
	XnUInt16 depth;
	count = 0;
	//printf("lastx: %d, lasty: %d last: %d",x,y, 640*y+x);
	//printf("\nFiltered input data, outputting point image");

		
		//points that dont meet requirement leave pointer in pointer array to be 0!
		for (y = 0; y < 480; y++)
		{
			for (x = 0; x < 640; x++)
			{
				depthValue = pDepth[(640*480-1)-(640*y+x)];


				if ((poff[(640*480-1)-(640*y+x)].z - depthValue)<0) {
					depth = 0;
				}
				else
				{
					depth =  poff[(640*480-1)-(640*y+x)].z - depthValue;
				}
				if (depthValue==0) {
					depth = 0;
				}
				if (depth<17) { //key setting variable HERE!!!!!!
					depth=0;
				}
				if (depth==0) { //if not considering, set the pointer to 0 (is reset each run)
					//filteredarray[(640*480-1)-(640*y+x)] = 0;
				}
				else
				{ //if the depth is valid, store it in the right place
					
					p1[count].z = depth;
					p1[count].x = x;
					p1[count].y = y;
					filteredarray[count] = &p1[count];
					count++;

					/*
					p1[(640*480-1)-(640*y+x)].z = depth;
					p1[(640*480-1)-(640*y+x)].x = x;
					p1[(640*480-1)-(640*y+x)].y = y;
					*/
				}
			}
		}


	//intarray2bmp ( "points1.bmp", (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)80, p1);
	return;
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
#include "DepthDataFrame.h"

DepthDataFrame::DepthDataFrame(int width1, int height1)
{
	height = height1;
	width = width1;
	data = (unsigned short*)malloc(width*height*sizeof(unsigned short));
}

DepthDataFrame::DepthDataFrame(unsigned short* data1, int width1, int height1)
{
	height = height1;
	width = width1;
	data = data1;
}

int DepthDataFrame::MaxDepth(){
	int max = 0;
	for (int i=0;i<height*width;i++) {
		if (data[i]>max) {
			max = data[i];
		}
	}
	return max;
}
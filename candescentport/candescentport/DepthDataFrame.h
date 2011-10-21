#ifndef DEPTHDATAFRAME_H
#define DEPTHDATAFRAME_H


#include <stdlib.h>

class DepthDataFrame
{
public: 
	unsigned short* data;
	int width;
	int height;

	DepthDataFrame(int width, int height);

	DepthDataFrame(unsigned short* data1,  int width1, int height1);

	int MaxDepth();

};

#endif
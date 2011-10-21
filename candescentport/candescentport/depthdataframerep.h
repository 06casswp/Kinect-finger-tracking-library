#ifndef DEPTHDATAFRAMEREP_H
#define DEPTHDATAFRAMEREP_H


#include "DepthDataFrame.h"

class DepthDataFrameRepository
{
public:
	DepthDataFrame* Load(char* path); //1 file per frame

	void Save(DepthDataFrame *frame, char* path);

};

#endif
#include "depthdataframerep.h"
#include <iostream>
#include <fstream>

DepthDataFrame* DepthDataFrameRepository::Load(char* path){
	std::ifstream myfile;
	int height;
	int width;
	myfile.open (path,std::ios::binary);
	myfile.read((char*)&height,sizeof(height));
	myfile.read((char*)&width,sizeof(width));
	DepthDataFrame *out = new DepthDataFrame(width, height);
	myfile.read((char*)&out->data,sizeof(unsigned short)*height*width);
	myfile.close();
	return out;
	//1 file per frame
}

void DepthDataFrameRepository::Save(DepthDataFrame *frame, char* path){
	std::ofstream myfile;
	myfile.open (path);
	myfile.write((char*)&frame->height,sizeof(frame->height));
	myfile.write((char*)&frame->width,sizeof(frame->width));
	myfile.write((char*)frame->data,frame->height*frame->width*sizeof(unsigned short)) ;
	myfile.close();

}
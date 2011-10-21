#include "histogram.h"
#include <stdlib.h>


Histogram::Histogram(int length1){
	data = (int*)malloc(length1*sizeof(int));
	length = length1;
}

void Histogram::Reset(){
	for (int i = 0; i < length; i++)
	{
		data[i] = 0;
	}

}

void Histogram::Increase(int depthValue){
	if (depthValue >= length)
	{
		return;
	}
	data[depthValue]++;

}

void Histogram::PostProcess(int points){
	for (int i = 1; i < length; i++)
	{
		data[i] += data[i - 1];
	}

	if (points > 0)
	{
		for (int i = 1; i < length; i++)
		{
			data[i] = (int)(256 * (1.0f - (data[i] / (float)points)));
		}
	}

}

int Histogram::GetValue(unsigned short depthValue){
	if (depthValue >= length)
	{
		return 0;
	}
	return data[depthValue];

}


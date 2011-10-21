#include "ContourScanner.h"
#include "BinaryMap.h"



BinaryMap* ContourScanner::Scan(BinaryMap *inputMapz){
	inputMap = inputMapz;
	result = new BinaryMap(inputMap->Width + 1, inputMap->Height + 1);
	//Parallel.Invoke(this.ScanHorizontal, this.ScanVertical);
	ScanHorizontal();
	ScanVertical();
	return result;


}

void ContourScanner::ScanHorizontal(){
	int width = result->Width; //making these local increases speed
	int height = result->Height;
	for (int y = 0; y < height; y++)
	{
		int lastValue = 0;
		for (int x = 0; x < width; x++)
		{
			ProcessValue(x, y, lastValue);
		}
	}


}

void ContourScanner::ScanVertical(){
	int width = result->Width; //making these local increases speed
	int height = result->Height;
	for (int x = 0; x < width; x++)
	{
		int lastValue = 0;
		for (int y = 0; y < height; y++)
		{
			ProcessValue(x, y, lastValue);
		}
	}


}

void ContourScanner::ProcessValue(int x, int y, int lastValue){
	int currentValue = inputMap->check(x,y);
	bool hasChanged = (currentValue != lastValue);

	if (hasChanged)
	{
		lastValue = currentValue;
		result->set(x,y,1);
	}


}
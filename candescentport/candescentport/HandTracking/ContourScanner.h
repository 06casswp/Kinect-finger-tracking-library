#ifndef CONTOURSCAN_H
#define CONTOURSCAN_H

#include "BinaryMap.h"

class ContourScanner
{
public:
	BinaryMap* inputMap;
	BinaryMap* result;


	BinaryMap* Scan(BinaryMap *inputMapz);

	void ScanHorizontal();

	void ScanVertical();

	void ProcessValue(int x, int y, int lastValue);
};

#endif 
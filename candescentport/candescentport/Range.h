#ifndef RANGE_H
#define RANGE_H

#include <vector>



class Range
{
public:
	int Min;
	int Max;
	Range(int Min, int Max);
	Range(std::vector<int> values);

	int value();
};

#endif 
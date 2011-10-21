#ifndef RANGE_H
#define RANGE_H

#include <vector>



class Range
{
public:
	float Min;
	float Max;
	Range(float Min, float Max);
	Range(std::vector<float> values);

	float value();
};

#endif 
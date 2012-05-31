#ifndef RANGE_H
#define RANGE_H

#include <vector>

struct rangedat
{
	unsigned short min;
	unsigned short max;
};


class rangefnc
{
public:
	void set(rangedat* dest, unsigned short min, unsigned short max);
	void set(rangedat* dest, rangedat* src);
	void set(rangedat* dest, unsigned short* ints, int size);
	unsigned short value(rangedat* dat);
};


#endif 
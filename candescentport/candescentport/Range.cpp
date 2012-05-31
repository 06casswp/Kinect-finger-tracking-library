#include "Range.h"


	void rangefnc::set(rangedat* dest, unsigned short min, unsigned short max){
		dest->max = max;
		dest->min = min;
	}
	void rangefnc::set(rangedat* dest, rangedat* src){
		dest->max = src->max;
		dest->min = src->min;
	}
	unsigned short rangefnc::value(rangedat* dat){
		return dat->max-dat->min;
	}
	
	void rangefnc::set(rangedat* dest, unsigned short* ints, int size)
	{
		dest->min = ints[0];
		dest->max = dest->min;
		int index = 0;
		for (index=0;index<size;index++) {
			if (ints[index]<dest->min) {
				dest->min = ints[index];
			}
			else if (ints[index]>dest->max) {
				dest->max = ints[index];
			}
		}
	}


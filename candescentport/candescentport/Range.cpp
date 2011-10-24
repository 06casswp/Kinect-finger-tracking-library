#include "Range.h"


Range::Range(int Min1, int Max1){
	Max = Max1;
	Min = Min1;
}
Range::Range(std::vector<int> values){
	//iterator
	Min = (int)*values.begin();
	Max = Min;
	float value;
	std::vector<int>::iterator iter;
	for (iter = values.begin();iter<values.end(); iter++) {
		value = (int)*iter;
		if (value>Max) {
			Max= value;
		}
		if (value<Min) {
			Min = value;
		}

	}


}
int Range::value(){
	return Max-Min;


}
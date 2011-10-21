#include "Range.h"


Range::Range(float Min, float Max){
	Range::Max = Max;
	Range::Min = Min;
}
Range::Range(std::vector<float> values){
	//iterator
	Range::Min;
	Range::Max = Range::Min;
	float value;
	std::vector<float>::iterator iter;
	for (iter = values.begin();iter<values.end(); iter++) {
		value = (float)*iter;
		Min = (((value) > (Min)) ? (value) : (Min));
		Max = (((value) < (Max)) ? (value) : (Max));
	}


}
float Range::value(){
	return Max-Min;


}
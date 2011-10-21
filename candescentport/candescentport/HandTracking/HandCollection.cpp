#include "HandCollection.h"

HandCollection::HandCollection(){
	handData = new std::vector<HandData*>;

}

HandCollection::HandCollection(std::vector<HandData*>* data){
	handData = data;

}

int HandCollection::Count(){
	std::vector<HandData*>::iterator iter;
	int a =0;
	for (iter=handData->begin();iter<handData->end();iter++) {
		a++;
	}

	return a;
}

bool HandCollection::HandsDetected(){
	return (Count()>0);

}

bool HandCollection::IsEmpty(){
	return (Count()==0);

}
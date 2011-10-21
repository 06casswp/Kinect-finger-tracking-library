#ifndef HANDCOLL_H
#define HANDCOLL_H

#include "HandData.h"
#include <vector>
class HandCollection
{
public:

	std::vector<HandData*>* handData;

	HandCollection();

	HandCollection(std::vector<HandData*>* data);

	std::vector<HandData*>* Hands;

	int Count();

	bool HandsDetected();

	bool IsEmpty();
};

#endif 
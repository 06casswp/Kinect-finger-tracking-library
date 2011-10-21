#ifndef FINGERPOINT_H
#define FINGERPOINT_H

#include "..\Point.h"
#include "..\ILocatable.h"

class FingerPoint : public ILocatable
{
public:
	Point* location;

	FingerPoint(Point* location);

	int Id;

	float X();

	float Y();

	float Z();


};

#endif 
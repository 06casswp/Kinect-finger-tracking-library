#ifndef POINT_H
#define POINT_H

class Point {
public:
	float x;
	float y;
	float z;
	Point(float x, float y, float z);
	Point(void* p);

	void adapt(float x, float y, float z);
	bool isZero();
	bool Equals(void* pnt);
};

#endif 
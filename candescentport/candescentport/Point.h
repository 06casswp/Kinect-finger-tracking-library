#ifndef POINT_H
#define POINT_H

class Point {
public:
	int x;
	int y;
	int z;
	double angle;
	Point(int x1, int y1, int z1);
	Point(void* p);
	Point(){
		x= 0;
		y=0;
		z=0;
	}

	//void adapt(float x1, float y1, float z1);
	bool isZero();
	bool Equals(void* pnt);
};

#endif 
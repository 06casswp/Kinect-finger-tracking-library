#ifndef point_H
#define point_H

struct point {
	short x;
	short y;
	short z;
	double angle;
};


class pointman {
public:
	void set (short x, short y, short z, point* dest);
	void set (point* dest, point* src);
	void reset (point* dest);
	bool isZero(point* p);
	bool Equals(point* p1, point* p2);
	double distance(point *p1, point *p2);
	double distance(float x1, float y1, float x2, float y2);
	void Center(point *p1, point *p2, point *dest); //ISSUE HERE. WHERE ARE THESE CREATED pointS NEEDED AND STORED AND HOW MANY ETC
};

#endif 
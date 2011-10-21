#ifndef SYSRECT_H
#define SYSRECT_H

class sysrect
{
public:
	int X;
	int Y;
	int width;
	int height;
	bool contains(int x, int y);
	sysrect::sysrect(int x, int y, int width1, int height1);
};


#endif
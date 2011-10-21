#ifndef BITMAP_H
#define BITMAP_H


class bitmap
{
public:
	int width;
	int height;
	unsigned char*red;
	unsigned char*blue;
	unsigned char*green;
	bitmap(int width1, int height1);
};

#endif
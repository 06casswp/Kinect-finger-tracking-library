#ifndef INTSIZE_H
#define INTSIZE_H

class intsize
{
public:
	int Width;
	int Height;


	intsize(int width, int height);
	bool operator==(const intsize &other) const;

};

#endif 
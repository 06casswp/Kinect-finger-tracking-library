#ifndef BINMAP_H
#define BINMAP_H



class BinaryMap
{
public:
	int** map, c; //2D array pointer to pointer (think args)


	BinaryMap(int** map, int width, int height);

	BinaryMap(int width, int height);

	int check(int x, int y); //was this[] does a check to see if within bounds

	bool set(int x,int y, int val);

	bool IsSet(int x, int y);

	int Width;

	int Height;

	float FillRate();

	bool IsOutOfBounds(int x, int y);
};

#endif 
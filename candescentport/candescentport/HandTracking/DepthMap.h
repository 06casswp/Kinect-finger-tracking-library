#ifndef DEPMAP_H
#define DEPMAP_H

struct depthmapdat
{
	int** map;

	int Width;

	int Height;

	bool used;
	
};

class DepthMapFnc
{
public:

	void create(depthmapdat* map, int width, int height);

	void copy(depthmapdat* dest,depthmapdat* src);

	void remove(depthmapdat* src);

	int check(depthmapdat* map,int x, int y); //was this[] does a check to see if within bounds

	bool set(depthmapdat* map,int x,int y, int val);

	bool IsSet(depthmapdat* map,int x, int y);

	float FillRate(depthmapdat* map);

	bool IsOutOfBounds(depthmapdat* map,int x, int y);

};

#endif 
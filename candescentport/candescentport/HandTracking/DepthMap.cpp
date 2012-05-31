#include "DepthMap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void DepthMapFnc::copy(depthmapdat* dest,depthmapdat* src){
	

}

void DepthMapFnc::create(depthmapdat* map, int width, int height){ //height (rows) //rowsxcolumns
	map->map = (int**)malloc(sizeof(int*) * width);
	map->Height = height;
	map->Width = width;
	memset(map->map,0,width*sizeof(int*));
	for(int c = 0; c < width; c++) {
		map->map[c] = (int*)malloc(sizeof(int) * height);
		memset(map->map[c],0,sizeof(int)*height);
	}
}

void DepthMapFnc::remove(depthmapdat* src) {
	if (src->map) {
		for(int c = 0; c < src->Width; c++) {
			free(src->map[c]);
		}
	free(src->map);
	}
}

int DepthMapFnc::check(depthmapdat* map,int x, int y){
	if (IsOutOfBounds(map, x, y)) {
		return 0;
	}
	return map->map[x][y];

} //was this[] does a check to see if within bounds
bool DepthMapFnc::set(depthmapdat* map,int x,int y, int val){
	if (IsOutOfBounds(map,x, y)) {
		return 0;
	}
	map->map[x][y] = val;
	return 1;

}


bool DepthMapFnc::IsSet(depthmapdat* map,int x, int y){
	if ((x<0)||(y<0)||(x>=map->Width)||(y>=map->Height)) {
		return 0;
	}

	return (map->map[x][y]==1);

}



float DepthMapFnc::FillRate(depthmapdat* map){
	int setCount = 0;
	int width = map->Width; //making these local increases speed
	int height = map->Height;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (IsSet(map, x, y))
			{
				setCount++;
			}
		}
	}
	return (float)setCount / (width * height);

}

bool DepthMapFnc::IsOutOfBounds(depthmapdat* map,int x, int y){
	return x < 0 || y < 0 || x >= map->Width || y >= map->Height;

}
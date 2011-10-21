#include "BinaryMap.h"
#include <stdlib.h>


BinaryMap::BinaryMap(int** maps, int width, int height){
	map = maps;
	Width = width;
	Height = height;
}

BinaryMap::BinaryMap(int width, int height){ //height (rows) //rowsxcolumns
	map = (int**)malloc(sizeof(int *) * height);
	for(c = 0; c < height; c++) {
		map[c] = (int*)malloc(sizeof(int) * width);
	}
	Width = width;
	Height = height;

}

int BinaryMap::check(int x, int y){
	if (IsOutOfBounds(x, y)) {
		return 0;
	}
	return map[x][y];

} //was this[] does a check to see if within bounds
bool BinaryMap::set(int x,int y, int val){
	if (IsOutOfBounds(x, y)) {
		return 0;
	}
	map[x][y] = val;
	return 1;

}


bool BinaryMap::IsSet(int x, int y){
	return (map[x][y]==1);

}



float BinaryMap::FillRate(){
	int setCount = 0;
	int width = Width; //making these local increases speed
	int height = Height;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (IsSet(y, y))
			{
				setCount++;
			}
		}
	}
	return (float)setCount / (width * height);

}

bool BinaryMap::IsOutOfBounds(int x, int y){
	return x < 0 || y < 0 || x >= Width || y >= Height;

}
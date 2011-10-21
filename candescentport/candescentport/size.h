#ifndef SIZE_H
#define SIZE_H


class Size {
public:
	float Width;
	float Height;
	int WidthInt();
	int HeightInt();

	Size(float width, float height);
	bool Equals(void* a);


};

#endif 
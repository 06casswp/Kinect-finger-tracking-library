#include "size.h"


Size::Size(float width, float height){
	Size::Width = width;
	Size::Height = height;
}
bool Size::Equals(void* a){
	Size* b = (Size*)a;
	if ((b->Width == Width)&&(b->Height == Height)) {
		return true;
	}
}

	int Size::WidthInt(){
		return (int)Width;

	}
	int Size::HeightInt(){
		return (int)Height;

	}
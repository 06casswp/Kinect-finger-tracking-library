#include "size.h"

	bool sizefnc::Equals(sizedat* s1, sizedat* s2){
		return ((s1->Height==s2->Height)&&(s1->Width==s2->Width));
	}
	void sizefnc::set (sizedat* s1, float width,float height){
		s1->Width = width;
		s1->Height = height;
	}





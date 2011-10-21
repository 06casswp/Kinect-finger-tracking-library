#include "intsize.h"	

intsize::intsize(int width, int height){
	intsize::Width = width;
	intsize::Height = height;
}

bool intsize::operator==(const intsize &other) const {
	if ((other.Height==Height)&&(other.Width==Width)) {
		return 1;
	}
	else
	{
		return 0;
	}
}
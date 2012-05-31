#ifndef SIZE_H
#define SIZE_H

struct sizedat {
	float Width;
	float Height;


};

class sizefnc {
public:
	bool Equals(sizedat* s1, sizedat* s2);
	void set (sizedat* s1, float width,float height);

};



#endif 
#include "rgbimagefact.h"       
#include <stdlib.h>
#include <math.h>


RGBImageFactory::RGBImageFactory(bitmap* target1, sysrect* area1){
	target = target1;
	area = area1;


}
/*
RGBImageFactory::RGBImageFactory(sysrect* area1){
	target = new bitmap(area1->width,area1->height);
	area = area1;

}
*/
void RGBImageFactory::CreateRgbImage(XnRGB24Pixel* pointer){

	unsigned short data;
	unsigned char red,green, blue;

	for (unsigned pos = 0; pos < area->width*area->height; pos++) {
		target->blue[pos] = pointer->nBlue;
		target->red[pos] = pointer->nRed;
		target->green[pos] = pointer->nGreen;
	}


}

void RGBImageFactory::WavelengthToRGB(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B) {

	double Gamma        =   0.80;
	double IntensityMax = 255;
	double Blue = 0;
	double factor = 0;
	double Green = 0;
	double Red = 0;


	if ((wavelength>=380)& (wavelength<=439)) {

		Red   = -(wavelength - 440) / (440 - 380);
		Green = 0.0;
		Blue  = 1.0;
	}
	if ((wavelength>=440)& (wavelength<=489)) {

		Red   = 0.0;
		Green = (wavelength - 440) / (490 - 440);
		Blue  = 1.0;
	}
	if ((wavelength>=490)& (wavelength<=509)) {

		Red   = 0.0;
		Green = 1.0;
		Blue  = -(wavelength - 510) / (510 - 490);
	}
	if ((wavelength>=510)& (wavelength<=579)) {

		Red   = (wavelength - 510) / (580 - 510);
		Green = 1.0;
		Blue  = 0.0;
	}
	if ((wavelength>=580)& (wavelength<=644)) {

		Red   = 1.0;
		Green = -(wavelength - 645) / (645 - 580);
		Blue  = 0.0;
	}
	if ((wavelength>=645)& (wavelength<=780)) {

		Red   = 1.0;
		Green = 0.0;
		Blue  = 0.0;
	}
	if ((wavelength>781)& (wavelength<380)) {
		Red  = 0.0;
		Green = 0.0;
		Blue  = 0.0;
	}



	// Let the intensity fall off near the vision limits

	if ((wavelength>=380)& (wavelength<=419)) {  
		factor = 0.3 + 0.7*(wavelength - 380) / (420 - 380);
	}
	if ((wavelength>=420)& (wavelength<=700)) {  
		factor = 1.0;
	}
	if ((wavelength>=701)& (wavelength<=780)) {  
		factor = 0.3 + 0.7*(780 - wavelength) / (780 - 700);
	}
	if ((wavelength<380)& (wavelength>780)) { 
		factor = 0.0;
	}



	*R = Adjust(Red,   factor);
	*G = Adjust(Green, factor);
	*B = Adjust(Blue,  factor);
}

char RGBImageFactory::Adjust(double color, double factor){
	double Gamma = 0.80;
	double IntensityMax = 255;
	if (color == 0) {
		return 0;
	}
	else
	{
		return (IntensityMax*pow(color*factor,Gamma));
	}
}

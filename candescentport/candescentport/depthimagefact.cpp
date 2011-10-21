#include "depthimagefact.h"
#include "bitmap.h"
#include "histogram.h"
#include <math.h>

DepthImageFactory::DepthImageFactory(bitmap *target1, Histogram *histogram1, sysrect* area1)
{
	target = target1;
	histogram = histogram1;
	area = area1;
}

void DepthImageFactory::CreateDepthImage(int* pointer, int width, int height)
{
	CreateHistogram(pointer);


	unsigned short data;
	unsigned char red,green, blue;
	double granularity = 360.0 / ((double)( max - min ) + 1);
	double wave;
	for (unsigned pos = 0; pos < area->width*area->height; pos++) {
		double hue = (pointer[ pos ] - min) * granularity;
		int    H = (int)( hue / 60 ) % 6;
		double F = (hue / 60) - H;
		double Q = 1.0 - F;

#define c( x ) (255 * x)
		switch (H)
		{
		case 0:  red = c(1);  green = c(F);  blue = c(0);  break;
		case 1:  red = c(Q);  green = c(1);  blue = c(0);  break;
		case 2:  red = c(0);  green = c(1);  blue = c(F);  break;
		case 3:  red = c(0);  green = c(Q);  blue = c(1);  break;
		case 4:  red = c(F);  green = c(0);  blue = c(1);  break;
		default: red = c(1);  green = c(0);  blue = c(Q);
		}
#undef c
		//blue = intarray[pos] & 0xFF;
		//intarray[pos] >> 8;
		//green = intarray[pos] & 0xFF;
		//red = intarray[pos] & 0xFF;
		//red = 0x00;


		wave = (double)pointer[pos]/10.0+380.0;

		WavelengthToRGB(wave, &red,&green,&blue);

		target->blue[pos] = blue;
		target->red[pos] = red;
		target->green[pos] = green;

	}

}

void DepthImageFactory::CreateHistogram(int* sourceData)
{
	histogram->Reset();

	int points = 0;
	unsigned short* pDepth = (unsigned short*)sourceData;
	for (int y = 0; y < area->height; ++y)
	{
		for (int x = 0; x < area->width; ++x, ++pDepth)
		{

			unsigned short depthVal = *pDepth;
			if (depthVal > 0)
			{
				histogram->Increase(depthVal);
				points++;
			}


		}
	}

	histogram->PostProcess(points);
}

void DepthImageFactory::WavelengthToRGB(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B) {

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

char DepthImageFactory::Adjust(double color, double factor){
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

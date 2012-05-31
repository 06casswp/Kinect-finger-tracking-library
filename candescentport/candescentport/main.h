#define NOMINMAX



#include "OpenNIDataSourceFactory.h"
#include "HandTracking/IHandDataSource.h"
#include "HandTracking/HandDataSourceSettings.h"
#include "HandTracking/HandDataSource.h"

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <Windows.h>
#include <WinUser.h>
void initogre();

class program
{
public:
	HandDataSource* handDataSource;
	ClusterDataSource* clusterdatsource;
	OpenNIDataSourceFactory* factory;
	void* other;
	OpenNIDataSourceFactory* CreateFactory();
	void CreateDataSources();
	
	void setoffset(const XnDepthPixel * sourceData,point *poff);
	void gotoxy ( short x, short y );
};





void WavelengthToRGB(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B);
char Adjust(double color, double factor);


namespace intarray2bmp
{

	//-------------------------------------------------------------------------- 
	// This little helper is to write little-endian values to file.
	//
	struct lwrite
	{
		unsigned long value;
		unsigned      size;
		lwrite( unsigned long value, unsigned size ):
		value( value ), size( size )
		{ }
	};

	//--------------------------------------------------------------------------
	inline std::ostream& operator << ( std::ostream& outs, const lwrite& v )
	{
		unsigned long value = v.value;
		for (unsigned cntr = 0; cntr < v.size; cntr++, value >>= 8)
			outs.put( static_cast <char> (value & 0xFF) );
		return outs;
	}

	//--------------------------------------------------------------------------
	// Take an integer array and convert it into a color image.
	//
	// This first version takes an array of array style of array:
	//   int* a[ 10 ]
	//
	// The second, overloaded version takes a flat C-style array:
	//   int a[ 10 ][ 10 ]
	//
	template <typename IntType>
	bool intarray2bmp(
		const std::string& filename,
		HandData*          cd,
		unsigned           rows,
		unsigned           columns,
		IntType            min_value,
		IntType            max_value
		) {
			// This is the difference between each color based upon
			// the number of distinct values in the input array.
			double granularity = 360.0 / ((double)( max_value - min_value ) + 1);
			double wave;
			// Open the output BMP file
			std::ofstream f( filename.c_str(),
				std::ios::out | std::ios::trunc | std::ios::binary );
			if (!f) return false;

			// Some basic
			unsigned long headers_size    = 14  // sizeof( BITMAPFILEHEADER )
				+ 40; // sizeof( BITMAPINFOHEADER )
			unsigned long padding_size    = (4 - ((columns * 3) % 4)) % 4;
			unsigned long pixel_data_size = rows * ((columns * 3) + padding_size);

			// Write the BITMAPFILEHEADER
			f.put( 'B' ).put( 'M' );                           // bfType
			f << lwrite( headers_size + pixel_data_size, 4 );  // bfSize
			f << lwrite( 0,                              2 );  // bfReserved1
			f << lwrite( 0,                              2 );  // bfReserved2
			f << lwrite( headers_size,                   4 );  // bfOffBits

			// Write the BITMAPINFOHEADER
			f << lwrite( 40,                             4 );  // biSize
			f << lwrite( columns,                        4 );  // biWidth
			f << lwrite( rows,                           4 );  // biHeight
			f << lwrite( 1,                              2 );  // biPlanes
			f << lwrite( 24,                             2 );  // biBitCount
			f << lwrite( 0,                              4 );  // biCompression=BI_RGB
			f << lwrite( pixel_data_size,                4 );  // biSizeImage
			f << lwrite( 0,                              4 );  // biXPelsPerMeter
			f << lwrite( 0,                              4 );  // biYPelsPerMeter
			f << lwrite( 0,                              4 );  // biClrUsed
			f << lwrite( 0,                              4 );  // biClrImportant

			// Write the pixel data
			// bottom-to-top
			FILE* fil;
			fil = fopen("a.txt","w");

			
			char* out = (char*)calloc(columns*rows,sizeof(char));
			
					
					int index = 0;
					for (index = 0; index<cd->clusterdata->allpointscnt; index++) {
						out[cd->clusterdata->Allpoints[index]->x+640*cd->clusterdata->Allpoints[index]->y] = cd->clusterdata->Allpoints[index]->z;
					}

					index = 0;
					int index1 = 0;
					for (index=0;index<cd->FingerpointCount;index++) {
						out[cd->Fingerpoints[index]->location->x+640*cd->Fingerpoints[index]->location->y] = 99;
						for (index1 = -10; index1<10; index1++) {
							out[std::max(0,cd->Fingerpoints[index]->location->x-index1)+640*cd->Fingerpoints[index]->location->y] = 99;
							out[cd->Fingerpoints[index]->location->x+640*std::max(0,cd->Fingerpoints[index]->location->y-index1)] = 99;
						}
					}
					

			for (int pos = 0; pos < columns*rows; pos++)  // left-to-right
			{
				unsigned char red, green, blue;

					// This is how we convert an integer value to a color:
					// by mapping it evenly along the CIECAM02 hue color domain.
					//
					// http://en.wikipedia.org/wiki/Hue
					// http://en.wikipedia.org/wiki/hsl_and_hsv#conversion_from_hsv_to_rgb
					//
					// The following algorithm takes a few shortcuts since
					// both 'value' and 'saturation' are always 1.0.
					

					/*
					/double hue = value%240;//(value - min_value) * granularity;
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


					//wave = (double)value/10.0+380.0;
					//fprintf(fil,"\n%u: %lf", pos, wave);
					//WavelengthToRGB(wave, &red,&green,&blue);
					*/

					f.put( static_cast <char> (out[pos]%240)  )
						.put( static_cast <char> (out[pos]%240) )
						.put( static_cast <char> (out[pos]%240)   );

				}
				if (padding_size) f << lwrite( 0, padding_size );
			
			fclose(fil);
			// All done!
			free(out);
			f.close();
			return 1;
	}


} // namespace intarray2bmp



// end intarray2bmp.hpp 


char Adjust(double color, double factor){
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


void WavelengthToRGB(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B) {

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





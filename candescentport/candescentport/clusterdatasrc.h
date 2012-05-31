#ifndef CLUSTERDATSRC_H
#define CLUSTERDATSRC_H


#include "clusterdatasrcsets.h"

#include "size.h"

#include <XnCppWrapper.h>

#include "iclusterdatasrc.h"
#include "idepthpntdatsource.h"
#include "datasourceprocessor.h"


#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
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

class ClusterDataSource : public IClusterDataSource
{
public:
	 
	ClusterDataSourceSettings* settings;

	void* clusterhelper;
	sizedat* size;
	
	int found;
	
	point** filteredarray;
	int count;

	clusterdat ** Process(const XnDepthPixel * sourceData, point *p1, point *poff, point** filtered);
	void FindpointsWithinDepthRange(const XnDepthPixel * datapointer, point *p1, point *poff);
	int width();
	int height();
	bool intarray2bmp(
		const std::string& filename,
		unsigned           rows,
		unsigned           columns,
		int            min_value,
		int            max_value,
		point *p1
		) {
			// This is the difference between each color based upon
			// the number of distinct values in the input array.
			double granularity = 360.0 / ((double)( max_value - min_value ) + 1);
			double wavelength;
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
			//FILE* fil;
			//fil = fopen("a.txt","w");


			unsigned short out[640*480] = {600};// = (unsigned short*)calloc(columns*rows,sizeof(unsigned short));
			memset(&out,0,640*480);
			int index = 0;
			for (index=0; index<640*480; index++) {
				out[640*(p1[index].y)+(p1[index].x)] = p1[index].z;
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
					double hue = (out[pos] - min_value) * granularity;
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

					*/


					wavelength = (double)out[pos]*5+380.0;
					//fprintf(fil,"\n%u: %lf", pos, wavelength);
					//WavelengthToRGB1(wave, &red,&green,&blue);
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

		Gamma = 0.80;
	  IntensityMax = 255;
	  if (Red == 0) {
		  red =  0;
	  }
	  else
	  {
		  red = (IntensityMax*pow(Red*factor,Gamma));
	  }
	  	  if (Green == 0) {
		  green =  0;
	  }
	  else
	  {
		  green = (IntensityMax*pow(Green*factor,Gamma));
	  }
		  	  	  if (Blue == 0) {
		  blue =  0;
	  }
	  else
	  {
		  blue = (IntensityMax*pow(Blue*factor,Gamma));
	  }

					f.put( static_cast <char> (red)  )
						.put( static_cast <char> (green) )
						.put( static_cast <char> (blue)   );

				}
				if (padding_size) f << lwrite( 0, padding_size );
			
			//fclose(fil);
			// All done!
			return f.good();
	}
};



  void WavelengthToRGB1(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B);
  char Adjust1(double color, double factor);


namespace intarray2bmp1
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
  bool intarray2bmp1(
    const std::string& filename,
    IntType*          intarray,
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
		//FILE* fil;
	//fil = fopen("a.txt","w");
      for (unsigned pos = 0; pos < columns*rows; pos++)  // left-to-right
        {
        unsigned char red, green, blue;
        //
      {
        // This is how we convert an integer value to a color:
        // by mapping it evenly along the CIECAM02 hue color domain.
        //
        // http://en.wikipedia.org/wiki/Hue
        // http://en.wikipedia.org/wiki/hsl_and_hsv#conversion_from_hsv_to_rgb
        //
        // The following algorithm takes a few shortcuts since
        // both 'value' and 'saturation' are always 1.0.
        /*
        double hue = (intarray[ pos ] - min_value) * granularity;
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

		*/
		wave = (double)intarray[(640*480-1)-pos]/10.0+380.0;
		//fprintf(fil,"\n%u: %lf", pos, wave);
		WavelengthToRGB1(wave, &red,&green,&blue);
		

        f.put( static_cast <char> (blue)  )
         .put( static_cast <char> (green) )
         .put( static_cast <char> (red)   );
        }

      if (padding_size) f << lwrite( 0, padding_size );
      }
	  //fclose(fil);
    // All done!
    return f.good();
    }

  } // namespace intarray2bmp

#endif 

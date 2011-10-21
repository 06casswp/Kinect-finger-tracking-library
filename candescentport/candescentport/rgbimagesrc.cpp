#include "rgbimagesrc.h"


RGBImageSource::RGBImageSource(IRGBPointerDataSource* dataSource){
	        CurrentValue = new bitmap(dataSource->Width, dataSource->Height);
            area = new sysrect(0, 0, dataSource->Width, dataSource->Height);
            imageFactory = new RGBImageFactory(CurrentValue, area);

}
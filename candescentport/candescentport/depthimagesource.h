#include "Iimagesource.h"
#include  "histogram.h"
#include "sysrect.h"
#include "depthimagefact.h"
#include "datasourceprocessor.h"
#include "bitmap.h"
#include "idepthpntdatsource.h"
#include "Iimagesource.h"

class DepthImageSource : public DataSourceProcessor<bitmap*, int*>, public IImageSource
{
public:
	Histogram* histogram;
	sysrect* area;
	DepthImageFactory* imageFactory;

	DepthImageSource(IDepthPointerDataSource* depthDataSource)
		: DataSourceProcessor(depthDataSource),IImageSource(){};


	int Width();

	int Height();



	bitmap* ProcessUnsafe(int* sourceData);
};
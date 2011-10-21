#ifndef DEPTHDATSRC_H
#define DEPTHDATSRC_H

#include "datasourcebase.h"
#include "DepthDataFrame.h"




class DepthDataSource : public DataSourceBase<DepthDataFrame, xn::DepthGenerator>
    {
	public:
		DepthDataSource(xn::DepthGenerator generator)
            : base(generator);

        void InternalRun();

        int Width();

        int Height();

        int MaxDepth();
    };


#endif 
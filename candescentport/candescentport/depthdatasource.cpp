#include "depthdatasource.h"
		


        int DepthDataSource::Width(){
			xn::DepthMetaData metadat;
			generator->GetMetaData(metadat);
			return metadat.XRes();

		}

        int DepthDataSource::Height(){
			xn::DepthMetaData metadat;
			generator->GetMetaData(metadat);
			return metadat.YRes();


		}

        int DepthDataSource::MaxDepth(){
			return generator->GetDeviceMaxDepth();

		}
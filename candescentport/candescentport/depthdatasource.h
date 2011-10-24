#ifndef DEPTHDATSRC_H
#define DEPTHDATSRC_H

#include "datasourcebase.h"
#include "DepthDataFrame.h"

class DepthDataSource : public DataSourceBase<DepthDataFrame*, xn::DepthGenerator*>
    {
	public:
		DepthDataSource(xn::DepthGenerator* generator)
			: DataSourceBase(generator){
				
				data = new DepthDataFrame(Width(),Height());
		
		}

		void DepthDataSource::InternalRun(){
			int size = Width()*Height()*sizeof(short);
			short * datas = (short*)malloc(size);
			memcpy(datas,generator->GetDepthMap(),size);
			memcpy(data,datas,size);
			OnNewDataAvailable(data);
			
		}

        int Width();

        int Height();

        int MaxDepth();
    };


#endif 
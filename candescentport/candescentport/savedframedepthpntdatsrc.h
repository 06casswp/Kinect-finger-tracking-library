
#include "intsize.h"
#include "idepthpntdatsource.h"
#include "DepthDataFrame.h"

class SavedFrameDepthPointerDataSource : public IDepthPointerDataSource//, IDisposable
{
	intsize* size;
	int maxDepth;

	SavedFrameDepthPointerDataSource(int width, int height, DepthDataFrame frame);

	int* GetPointer(DepthDataFrame frame);

	

	int MaxDepth();


	bool IsRunning();

	int* CurrentValue;

	void Push();



	void Dispose();
};

#include "intsize.h"
#include "idepthpntdatsource.h"
#include "DepthDataFrame.h"

class SavedFrameDepthPointerDataSource : public IDepthPointerDataSource//, IDisposable
{
	intsize* size;
	int maxDepth;
	unsigned short* CurrentValue;

	SavedFrameDepthPointerDataSource(int width, int height, DepthDataFrame* frame){
		size = new intsize(width,height);
		maxDepth = frame->MaxDepth();
		CurrentValue = GetPointer(frame);
	}

	unsigned short* GetPointer(DepthDataFrame* frame){
		unsigned short* pointerToMemory = (unsigned short*)malloc(frame->height*frame->width*2);
		memcpy(pointerToMemory,frame->data,frame->height*frame->width*2);
		return pointerToMemory;
	}

	void Start() {
	}

	void Stop() {


	}

	bool IsRunning() {
		return true;
	}

	void Push() {
		//if (!(NewDataAvailable==0)) {
		//	NewDataAvailable(CurrentValue);
		//}
	}

	//void Dispose();
};
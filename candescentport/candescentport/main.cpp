#define _CRTDBG_MAP_ALLOC




#include <stdlib.h>
#include <crtdbg.h>

#include "main.h"

#include "render.h"

//pointer to an array of pointers

point p1[640*480];
point poffsets[640*480];

point *pa1[640*480]; //the array of pointers to the current points (this is what is passed through as the original filtered data set)
point **filtered;

int contours;
int hulls;



void program::gotoxy ( short x, short y )
{
//COORD coord = {x, y};
//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
SetCursorPos(x,y);
}

int main() {
	contours = 0;
	extern int contours;// = 0;
	hulls = 0;
	extern int hulls;

	MyApplication* app = new MyApplication();

	app->logit = true;
	app->startup();
	
	memset(&p1,0,sizeof(p1));
	memset(&poffsets,0,sizeof(poffsets));
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	int i = 0;
	for (i=0;i<(640*480);i++) {
		pa1[i] = &p1[i];
	}
	filtered = &pa1[0];

	//printf("Hold the escape key to terminate program\nProgram Start");
	program pro;
	//printf("%d",sizeof(OpenNIDataSourceFactory));
	pro.factory = new OpenNIDataSourceFactory;
	
	pro.handDataSource = new HandDataSource();

	pro.handDataSource->start();
	if (!pro.factory->init("Config.xml")) {
		pro.factory->context.Release();
		delete pro.factory;
		delete pro.handDataSource;
		
		return 1;
	}
	pro.CreateDataSources(); 
	pro.factory->context.StartGeneratingAll();

	//printf("\nOpenNI starting Generating\n");

	int handsfing = 0;
	//has a start function, then it has a callback function on newdataavailable
	//start generating
	int it = 0;
	float x[3] = {0};
	float y[3] = {0};
	bool resetoff = false;
	app->guihand->resetoff = false;
	while(!app->_listener->_shutdown) {
		resetoff = app->guihand->resetoff;

		if ( app->window->isClosed() ) app->_listener->_shutdown = true; // or "break"

		if ( !app->window->isActive() && ( !app->window->isClosed() ) ) {
			//WaitMessage(); // on Windows operating system, include windows.h
		}
		if (!app->_listener->_shutdown) {
		
			//for (i=0;i<(640*480);i++) {
			//	pa1[i] = &p1[i];
			//}
			if ((0)||(poffsets[2].x==0)||(resetoff)) {
				app->guihand->resetoff = false;
				pro.factory->context.WaitOneUpdateAll(pro.factory->depthgen);
				pro.setoffset(pro.factory->depthgen.GetDepthMap(),&poffsets[0]);
			}
			else
			{
				it++;
				memset(&p1,0,sizeof(p1)); //reset points
				//reset clusterdats (reset point pointer arrays and associated data)
				//wait for
				pro.factory->context.WaitOneUpdateAll(pro.factory->depthgen);
				//pass to clusterdat
				//printf("\nGenerating clusterdats");
				QueryPerformanceCounter(&start);

				clusterdat**cd = pro.clusterdatsource->Process(pro.factory->depthgen.GetDepthMap(),&p1[0],&poffsets[0],filtered);
				
				

				

				//printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b%lf", ((finish.QuadPart - start.QuadPart) / (double)freq.QuadPart));
				//pass clusterdat to hand
				//printf("\nOutputting clusterdats to Image");

				for (i=0;i<2;i++) {
					if (cd) {
						if (cd[i]) {
							char name[10];
							char temp[4];
							strcpy(&name[0],"c");
							_itoa(i,temp,10);
							strcat(&name[0],temp);
							strcat(&name[0],".bmp");
							//intarray2bmp::intarray2bmp <unsigned __int16> (name, cd[i], (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );
						}
					}
				}
				//printf("\nhulls %d, contours %d",hulls,contours);
				app->resetcube();
				if (cd) {
					//printf("\nGenerating Hand Data - contours: %d",contours);
					HandCollection* HC = pro.handDataSource->Process(cd,pro.clusterdatsource->size,pro.clusterdatsource->found);
					if (HC) {
						//printf("\nHands Found: %d",HC->count);
						int g = 0;
						app->assigned = 0;
						for (g = 0;g<HC->count;g++) {
							//printf("\nFingers found: %d",HC->hands[g]->FingerpointCount);
							if (HC->hands[g]->FingerpointCount>0) {
								char name[10];
								char temp[4];
								strcpy(&name[0],"c");
								_itoa(handsfing,temp,10);
								strcat(&name[0],temp);
								strcat(&name[0],".bmp");
								//intarray2bmp::intarray2bmp <unsigned __int16> (name, HC->hands[g], (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );
								handsfing++;
								app->drawcube(HC->hands[g]);
							
								
							}
						}
						if (HC->hands[0]->FingerpointCount>0) {
							int ihh = 0;
							for (ihh=0;ihh<2;ihh++) {
								x[ihh] = x[ihh+1];
							}
							
							for (ihh=0;ihh<2;ihh++) {
								y[ihh] = y[ihh+1];
							}
							
							float xf = (((float)HC->hands[0]->Fingerpoints[0]->location->x/640));
							float yf = (((float)HC->hands[0]->Fingerpoints[0]->location->y/480));
							xf*=2.0f;
							
						
							yf*=2.0f;
							
							float x1 = (float)xf*(float)1280;
							float y1 = (float)yf*(float)720;
							x[2] = x1;
							float xtot = 0;
							for (int i=0;i<2;i++) {
								xtot += x[i];
							}
							xtot = xtot/3;
							y[2] = y1;
							float ytot = 0;
							for (int i=0;i<2;i++) {
								ytot += y[i];
							}
							ytot = ytot/3;
							pro.gotoxy((short)xtot,(short)ytot);
							INPUT    Input={0};	
							ZeroMemory(&Input,sizeof(INPUT));
							if (HC->hands[0]->Fingerpoints[0]->location->z<20) {
																				// Create our input.

								Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
								Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
								SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.

								ZeroMemory(&Input,sizeof(INPUT));
																Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
								Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
								SendInput( 1, &Input, sizeof(INPUT) );	
								// Fills a block of memory with zeros.
							// Send the input.
							}
							if (HC->hands[0]->Fingerpoints[0]->location->z>20) {

							}
						}
					}
					else
					{
						//printf("\nHands Found: 0");
					}

				}
				QueryPerformanceCounter(&finish);
				//printf("%lf\n",double(finish.QuadPart-start.QuadPart)/freq.QuadPart);
				if ( app->window->isClosed() ) app->_listener->_shutdown = true; // or "break"
				if (!app->_listener->_shutdown) {
					app->renderOneFrame();
				}

				unsigned int width,height, colourdepth;
				int left,top;
				app->window->getMetrics(width,height,colourdepth,left,top);
				POINT point;
				
				
				if (GetCursorPos(&point)) {
					if ((app->window->isActive())&&(point.x>left)&&(point.x<left+width)&&(point.y>top)&&(point.y<top+height)) {
						CEGUI::MouseCursor::getSingleton().setVisible(true);
						app->inputhand->setmouse(point.x-left-8,point.y-top-30);
					}
					else
					{
						CEGUI::MouseCursor::getSingleton().setVisible(false);
					}	
				}
			}




		}
	}
	delete app;
	pro.factory->context.Release();
	delete pro.factory;
	delete pro.handDataSource;
	
	
	return 0;
}

void program::CreateDataSources()
{
	printf("\nCreating Data Sources");

	//settings.DetectCenterOfPalm = false; //Not used, so disabling this makes the app faster
	clusterdatsource = factory->CreateClusterDataSource1();

}



void program::setoffset(const XnDepthPixel * sourceData,point *poff){
	//intarray2bmp1::intarray2bmp1 <unsigned __int16> ( "orig.bmp", (unsigned __int16*)sourceData, (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );
	unsigned short maxval=10;
	XnUInt16* pDepth = (XnUInt16*)sourceData;
	unsigned __int16 sourceData1[640*480];
	memset(&sourceData1[0],0,sizeof(sourceData1));
	int x,y;
	XnUInt16 depthValue;
	for (y = 0; y < 480; y++)
	{
		for (x = 0; x < 640; x++)
		{
			depthValue = pDepth[(640*480-1)-(640*y+x)];
			if (!(depthValue==0)) {
				if (maxval>depthValue) { 
					maxval = depthValue;
				}
			}
			else
			{
				depthValue = maxval;

			}
			poff[(640*480-1)-(640*y+x)].z = depthValue;
			sourceData1[(640*480-1)-(640*y+x)] = depthValue;
			poff[(640*480-1)-(640*y+x)].x = x;
			poff[(640*480-1)-(640*y+x)].y = y;
		}
	}
	//intarray2bmp1::intarray2bmp1 <unsigned __int16> ( "offsetssss.bmp", &sourceData1[0], (unsigned short)480, (unsigned short)640, (unsigned __int16)0, (unsigned __int16)3000 );
}

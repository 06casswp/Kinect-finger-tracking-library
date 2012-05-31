#include "framelisten.h"
#include "GUI.h"

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt)

{
	lasttime = time;
	QueryPerformanceCounter(&tick);
	time.QuadPart = tick.QuadPart;




	diff = (double)(time.QuadPart-lasttime.QuadPart)/((double)tickspersecond.QuadPart);
	


	_Keyboard->capture();
	_Mouse->capture();
	Ogre::Vector3 translate(0,0,0);
	
	if (_inputhand->retrievedown(200)>0) { //up arrow
		translate += Ogre::Vector3(0,0,1);
	}
	if (_inputhand->retrievedown(208)>0) { //down arrow
		translate += Ogre::Vector3(0,0,-1);
	}
	if (_inputhand->retrievedown(49)>0) { //N
		translate += Ogre::Vector3(0,1,0);
	}
	if (_inputhand->retrievedown(50)>0) { //M
		translate += Ogre::Vector3(0,-1,0);
	}
	if (_inputhand->retrievedown(203)>0) { //left arrow
		translate += Ogre::Vector3(1,0,0);
	}
	if (_inputhand->retrievedown(205)>0) { //right arrow
		translate += Ogre::Vector3(-1,0,0);
	}
	translate *= 5;
	_Cam->setPosition(translate+_Cam->getPosition());
	_Cam->lookAt(0,0,0);
	





	if ( CEGUI::System::getSingletonPtr() )
    CEGUI::System::getSingleton().injectTimePulse( evt.timeSinceLastFrame );

	if ((_inputhand->retrievedown(56)>0)&&(_inputhand->retrievedown(62)>0)) {
		guiz* temp = (guiz*)guihand;
		temp->destroyall();
		_shutdown = true;
	}
	if (_shutdown) {
		return false;
	}
	_inputhand->reset();
	return true;
}




bool MyFrameListener::keyPressed( const OIS::KeyEvent &arg )
{
	_inputhand->keyevent(1,arg);

	return true;
}
//-------------------------------------------------------------------------------------
bool MyFrameListener::keyReleased( const OIS::KeyEvent &arg )
{
	_inputhand->keyevent(2,arg);

	return true;
}
//-------------------------------------------------------------------------------------
bool MyFrameListener::mouseMoved( const OIS::MouseEvent &arg )
{
	_inputhand->mousemove(arg);

	return true;
}
//-------------------------------------------------------------------------------------
bool MyFrameListener::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	_inputhand->mouseevent(1, id);

	return true;
}
//-------------------------------------------------------------------------------------
bool MyFrameListener::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	_inputhand->mouseevent(2, id); 

	return true;
}
//-------------------------------------------------------------------------------------

void MyFrameListener::updateInfo()
{
	Ogre::String currFps  = "Current FPS: ";
	Ogre::String avgFps   = "Average FPS: ";
	Ogre::String bestFps  = "Best FPS: ";
	Ogre::String worstFps = "Worst FPS: ";
	Ogre::String tris     = "Triangle Count: ";
	Ogre::String batches  = "Batch Count: ";
	
	char data[1000] = {'\0'};




	
		Ogre::OverlayElement* guiAvg     = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		Ogre::OverlayElement* guiCurr    = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		Ogre::OverlayElement* guiBest    = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		Ogre::OverlayElement* guiWorst   = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		const Ogre::RenderTarget::FrameStats& stats = m_Window->getStatistics();
		guiAvg->setCaption(avgFps + Ogre::StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption(currFps + Ogre::StringConverter::toString(stats.lastFPS));
		guiBest->setCaption(bestFps + Ogre::StringConverter::toString(stats.bestFPS) + " " + Ogre::StringConverter::toString(stats.bestFrameTime) + " ms");
		guiWorst->setCaption(worstFps + Ogre::StringConverter::toString(stats.worstFPS) + " " + Ogre::StringConverter::toString(stats.worstFrameTime) + " ms");

		Ogre::OverlayElement* guiTris    = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		guiTris->setCaption(tris + Ogre::StringConverter::toString(stats.triangleCount));

		Ogre::OverlayElement* guiBatches = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
		guiBatches->setCaption(batches + Ogre::StringConverter::toString(stats.batchCount));

		Ogre::OverlayElement* guiDbg     = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/DebugText");



}
void MyFrameListener::Init(Ogre::RenderWindow *mWindow)
{
	m_Window      = mWindow;
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	Ogre::Overlay *m = Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay");
	if(m) m->show();
}





MyFrameListener::MyFrameListener(Ogre::RenderWindow* win,Ogre::Camera*cam,Ogre::Viewport* viewport)
{
	_InputManager = NULL;
	_listener = NULL;
	_Keyboard = NULL;
	_Mouse = NULL;
	_Cam = NULL;


	_viewport = NULL;

	_node = NULL;


	m_Window = NULL;


	//init stuff
	keydown1 = false;
	
	QueryPerformanceFrequency(&tickspersecond);
	keydown = false;

	QueryPerformanceCounter(&tick);
	lasttime.QuadPart = tick.QuadPart/tickspersecond.QuadPart;
	_shutdown = false;
	m_Window = win;
	_Cam = cam;

	_movementspeed = 1000000000.0f;
	_viewport = viewport;
	_comp1 = false;
	_comp2 = false;
	_comp3 = false;
	_down1 = false;
	_down2 = false;
	_down3 = false;
	_WalkingSpeed = 10000000.0f;


	Init(win);
	OIS::ParamList parameters;


		#if defined OIS_WIN32_PLATFORM
    parameters.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    parameters.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    parameters.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    parameters.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
    #elif defined OIS_LINUX_PLATFORM
    parameters.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    parameters.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    parameters.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    parameters.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
    #endif

	unsigned int windowHandle = 0;
	std::ostringstream windowHandleString;
	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));
	_InputManager = OIS::InputManager::createInputSystem(parameters);
	_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject( OIS::OISKeyboard, true ));
	_Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject( OIS::OISMouse, true ));

	_Mouse->setEventCallback(this);
	_Keyboard->setEventCallback(this);



}

MyFrameListener::~MyFrameListener()
{
	_InputManager->destroyInputObject(_Keyboard);
	_InputManager->destroyInputObject(_Mouse);
	OIS::InputManager::destroyInputSystem(_InputManager);

}


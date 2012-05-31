



#include "GUI.h"
#include <CEGUI.h>//
#include <RendererModules\Ogre\CEGUIOgreRenderer.h>//
#include <Ogre.h>



void guiz::mainGUI() {
	
	
	
	CEGUI::MouseCursor::getSingleton().setVisible(true);

	CEGUI::System::getSingleton().setGUISheet(M);
}

void guiz::unloadmain() {

	CEGUI::MouseCursor::getSingleton().setVisible(true);//

}

guiz::~guiz() {

	destroyall();

	//removelogwin();
	_wmgr->destroyAllWindows();
	//need to destroy the existing stuff


}


guiz::guiz(Ogre::SceneManager* _SM, Ogre::Camera* _camera,inputz* inputhand, int windh, int windw) {
	windheight = windh;
	windwidth = windw;
	listener = NULL;
	inputman = NULL;
	_sceneManager = NULL;
	camera = NULL;
	_wmgr = NULL;
	sheet = NULL;
	pressedkey = 0;
	camera = _camera;
	_sceneManager = _SM;
	active = true;
	inputman = inputhand;
	resetmouse = false;
}


void guiz::destroyall() {
	

	return;
}


void guiz::initwm() {
	_wmgr = (CEGUI::WindowManager*)&CEGUI::WindowManager::getSingleton();
	sheet = _wmgr->createWindow("DefaultWindow", "GUI");
	loadallelem();
}

void guiz::loadallelem() {
	//exit button
	//settings button
	//reset offset button

	M = _wmgr->createWindow("DefaultWindow","Main");
	sheet->addChildWindow(M);


	exitbtn = _wmgr->createWindow("TaharezLook/Button","Main/Exitbtn");
	exitbtn->setText("Exit");
	exitbtn->setSize(CEGUI::UVector2(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.05f,0)));
	exitbtn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.0f,0)));
	M->addChildWindow(exitbtn);
	exitbtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&guiz::exitfnc,this));

	resetbtn = _wmgr->createWindow("TaharezLook/Button","Main/Resetbtn");
	resetbtn->setText("Reset Offset");
	resetbtn->setSize(CEGUI::UVector2(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.05f,0)));
	resetbtn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.150f,0),CEGUI::UDim(0.0f,0)));
	M->addChildWindow(resetbtn);
	resetbtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&guiz::reset,this));
	/*
	settingsbtn = _wmgr->createWindow("TaharezLook/Button","Main/Settingsbtn");
	settingsbtn->setText("Settings");
	settingsbtn->setSize(CEGUI::UVector2(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.05f,0)));
	settingsbtn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.30f,0),CEGUI::UDim(0.0f,0)));
	M->addChildWindow(settingsbtn);
	settingsbtn->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&guiz::settingsfnc,this));
	*/
}

	bool guiz::exitfnc(const CEGUI::EventArgs &e)
	{

		listener->_shutdown = true;
		return true;
	}
	bool guiz::settingsfnc(const CEGUI::EventArgs &e){


		return true;
	}
	bool guiz::reset(const CEGUI::EventArgs &e){

		resetoff = true;
		return true;
	}
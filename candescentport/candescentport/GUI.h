#pragma once
//handles all GUI and overlay stuff including the HUD
#ifndef _GUI_H__
#define _GUI_H__

#include <Ogre.h>
#include <CEGUI.h>//

#include <RendererModules\Ogre\CEGUIOgreRenderer.h>//
#include "inputman.h"

#include "framelisten.h"


//elements updated by network must be created at start and always available!


struct keyhold
{

	CEGUI::Window* button; //gets button name
	CEGUI::Window* actionname; //gets action name if one


};

struct layouts
{
	float x;
	float y;
	float width;
	float height;
	char* name;

};


class guiz
{
public:
	MyFrameListener* listener;
	inputz *inputman;
	bool active;
	Ogre::SceneManager* _sceneManager;
	Ogre::Camera* camera;

	bool resetmouse;
	CEGUI::WindowManager *_wmgr;
	CEGUI::Window *sheet;

	CEGUI::Window *M;
	CEGUI::Window* exitbtn;
	CEGUI::Window* resetbtn;
	CEGUI::Window* settingsbtn;

	bool first;


	bool exitfnc(const CEGUI::EventArgs &e); //exit button actuator
	bool settingsfnc(const CEGUI::EventArgs &e);
	bool reset(const CEGUI::EventArgs &e);

	bool resetoff;
	



	CEGUI::Window *GS; //game stuff ie HUD


	void removeallelem();
	//-----
	void mainGUI();
	void unloadmain();

	bool quit(const CEGUI::EventArgs &e);

	void initwm();



	int pressedkey;
	int pressedmap;
	int pressedaction;

void loadallelem();


void destroyall();
	int windheight;
	int windwidth;
	guiz(Ogre::SceneManager* _sceneManager, Ogre::Camera* _camera,inputz* inputhand, int windh, int windw);
	~guiz();
};




#endif
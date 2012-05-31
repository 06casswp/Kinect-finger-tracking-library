#pragma once
//inputs are injected here and distributed as appropriate
#ifndef _inputman_H__
#define _inputman_H__

#include "../OIS/OIS.h"
#include "CEGUI.h"//
#include "RendererModules\Ogre\CEGUIOgreRenderer.h"



struct button
{
	bool down;
	int pressed;
};



class inputz
{
public:

	bool crazyed; //are we handling results or is CEGUI
	float MX;
	float MY;
	
	float X;
	float Y;
	float maxX;
	float maxY;


	CEGUI::System *sys;
	int count;


	button bid[238]; 


	int retrievecount(int actionid);
	int retrievedown(int actionid);


	void keyevent(int type, const OIS::KeyEvent &arg);
	void mouseevent(int type, OIS::MouseButtonID id);

	void mousemove(const OIS::MouseEvent &arg);
	void resetmouse(float X1, float Y1);

	

	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

	void reset();
	void resetdown();

	void setmouse(int x,int y);

	inputz();


};



#endif
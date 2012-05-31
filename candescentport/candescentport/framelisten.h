#ifndef framel_H
#define framel_H

#include "ogre.h"
#include "CEGUI.h"
#include "..\OIS\OIS.h"
#include "inputman.h"


class MyFrameListener : public Ogre::FrameListener, Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
	void* guihand;
	OIS::InputManager* _InputManager;
	MyFrameListener* _listener;
	OIS::Keyboard* _Keyboard;
	OIS::Mouse* _Mouse;
	Ogre::Camera* _Cam;
	int X,Y;
	double _movementspeed;
	Ogre::Viewport* _viewport;
	bool _comp1, _comp2, _comp3;
	bool _down1, _down2, _down3;
	float _WalkingSpeed;
	Ogre::SceneNode* _node;

	Ogre::RenderWindow* m_Window;

	LARGE_INTEGER tickspersecond;
	LARGE_INTEGER lasttime;
	LARGE_INTEGER time;
	LARGE_INTEGER tick;
	double diff;
	bool _shutdown;
	inputz * _inputhand;
	int MX;
	int MY;
	bool keydown;
	bool keydown1;



	bool frameStarted(const Ogre::FrameEvent& evt);
	bool keyPressed( const OIS::KeyEvent &arg );
	//-------------------------------------------------------------------------------------
	bool keyReleased( const OIS::KeyEvent &arg );
	//-------------------------------------------------------------------------------------
	bool mouseMoved( const OIS::MouseEvent &arg );
	//-------------------------------------------------------------------------------------
	bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	//-------------------------------------------------------------------------------------
	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	//-------------------------------------------------------------------------------------



	void updateInfo();
	void Init(Ogre::RenderWindow *mWindow);





	MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera*cam, Ogre::Viewport* viewport);
	~MyFrameListener();

};


#endif 
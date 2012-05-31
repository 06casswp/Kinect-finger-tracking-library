#ifndef render_H
#define render_H


#include "ogre.h"
#include "CEGUI.h"
#include "..\OIS\OIS.h"
#include "RendererModules\Ogre\CEGUIOgreRenderer.h"
#include "framelisten.h"
#include "GUI.h"
#include "inputman.h"
#include "HandTracking/HandData.h"

class MyApplication
{
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	bool _keepRunning;

	Ogre::SceneNode* _Allnode;


	Ogre::Camera* camera;

	bool mShutDown;
	Ogre::Viewport* viewport;

	

	
	CEGUI::Font* font;


	Ogre::SceneNode                *mNode;
	Ogre::Entity                   *mEntity;

	Ogre::SceneNode *cubes;

	Ogre::SceneNode *cubehold[50];

public:
	bool config;
	bool logit;
	Ogre::RenderWindow* window;
	inputz* inputhand;
	MyFrameListener* _listener;
	int windwidth;
	int windheight;
	guiz* guihand;
	
	int assigned;
	void loadResources();

	int startup();
	void renderOneFrame();
	bool keepRunning();




	void createScene();
	void drawcube(HandData* hd);
	void resetcube();

	MyApplication();

	~MyApplication();



	};


#endif 
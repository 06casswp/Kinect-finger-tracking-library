#include "render.h"


	void MyApplication::loadResources()
	{
		char exepath[1000];
		GetCurrentDirectoryA(sizeof(exepath), exepath  );
		Ogre::ConfigFile cf;
		cf.load("resources.cfg");
		Ogre::String sectionName, typeName, dataname; //have 2, one for game resources which are common and another for universe resources

		Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
		while (sectionIter.hasMoreElements())
		{
			sectionName = sectionIter.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{


				typeName = i->first;
				dataname = Ogre::String(exepath);
				dataname += i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataname, typeName, sectionName);

			}
		}
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	}

	int MyApplication::startup()
	{

		Ogre::LogManager* logger =NULL;
		_root = NULL;
		
		try
		{
			logger = new Ogre::LogManager();
			_root = new Ogre::Root("plugins.cfg","settings.cfg"); //?
		}
		catch (std::bad_alloc &ba) {
			std::cout<<ba.what()<<std::endl;
			if (NULL!=logger)
				delete logger;
			if (NULL!=_root)
				delete _root;
			return 1;
		}

		logger->createLog("fingertracker.log", true, logit, false); // default output, to console output, supress file log




		FILE *conf; //pointer for db file
		fopen_s(&conf,"flag","r");
		if ((!conf==NULL)|config) {
			if (!conf==NULL) {
				fclose(conf);
			}
			if(!_root->showConfigDialog()){
				_keepRunning = false;
				return false;

			} else {
				_root->saveConfig();
			}
		}else
		{


			fopen_s(&conf,"settings.cfg","r");
			if (!conf==NULL) {
				fclose(conf);
				_root->restoreConfig();
			}
			else {
				if(!_root->showConfigDialog()){
					_keepRunning = false;
					return false;

				} else {
					_root->saveConfig();
				}
			}
		}


		fopen_s(&conf,"flag","w");
		if (conf) {
			fclose(conf);
		}
		window = _root->initialise(true,"FingerTrack 0.01A");

		_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

		remove( "flag" );

		camera = _sceneManager->createCamera("Camera");



		Ogre::PolygonMode mode = Ogre::PM_SOLID;

		camera->setPosition(Ogre::Vector3(0,800,-1));
		camera->lookAt(Ogre::Vector3(0,0,0));
		camera->setNearClipDistance(10); 
		camera->setFarClipDistance(10000); 
		camera->setPolygonMode(mode);



		viewport = window->addViewport(camera,0);//,0,0,.5,.5);
		viewport->setBackgroundColour(Ogre::ColourValue(0,0,0,0));


		




		camera->setAspectRatio(Ogre::Real(viewport->getActualWidth())/Ogre::Real(viewport->getActualHeight()));

		inputhand = new inputz(); 
		inputhand->maxX = viewport->getActualWidth()/2;
		inputhand->maxY = viewport->getActualHeight()/2;
		windwidth = viewport->getActualWidth();
		windheight = viewport->getActualHeight();
		guihand = new guiz(_sceneManager,camera,inputhand,windheight,windwidth);
		loadResources(); //loads the resources



		CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem();

		//resources for cegui
		CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");



		CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
		CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");
		CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
		CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());
		CEGUI::MouseCursor::getSingleton().setVisible(false);


		inputhand->sys = &CEGUI::System::getSingleton();

		

		const Ogre::Real _time_step = 0.5;
		const Ogre::Real time_scale = Ogre::Real(1.7);
		const Ogre::Real max_frame_time = Ogre::Real(1.0 / 4);
		






		guihand->initwm();

		_listener = new MyFrameListener(window,camera, viewport);
		_listener->_inputhand = inputhand;
		guihand->listener = _listener;
		_listener->guihand = (void*)guihand;
		_root->addFrameListener(_listener);




		

		//guihand->begin();
		guihand->mainGUI();



		createScene();



		bool enabled = true;		
		return 0;
	}

	void MyApplication::renderOneFrame()
	{
		Ogre::WindowEventUtilities::messagePump();
		_keepRunning = _root->renderOneFrame();
	}
	bool MyApplication::keepRunning()
	{	
		if (_listener->_shutdown) {
			_keepRunning = false;
		}
		return _keepRunning;
	}




	void MyApplication::createScene()
	{


		_sceneManager->setAmbientLight(Ogre::ColourValue(1, 1, 1));
		//_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 

 
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
		Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 640, 480, 1, 1, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
		Ogre::Entity* entGround = _sceneManager->createEntity("GroundEntity", "ground");
		_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
		entGround->setMaterialName("background");
		entGround->setCastShadows(false);


		cubes = _sceneManager->getRootSceneNode()->createChildSceneNode();




		Ogre::String name;
		char temp1[100];
		for (int i=0; i<49; i++) {
		name = "cube";
		name += itoa(i,temp1,10);
			cubehold[i] = cubes->createChildSceneNode(name);
			name +="ent";
			Ogre::Entity* cube = _sceneManager->createEntity(name,"cube.mesh");
			cube->setMaterialName("cubes");
			cube->setCastShadows(false);
			cubehold[i]->attachObject(cube);
			cubehold[i]->setScale(0.1f,0.1f,0.1f);
		}


	}



	MyApplication::MyApplication()
	{
		_keepRunning = true;
		mShutDown = false;
	
	
		_sceneManager = NULL;
		_root = NULL;



		_Allnode = NULL;

		camera = NULL;

		viewport = NULL;

		_listener = NULL;

		font = NULL;

		mNode = NULL;
		mEntity = NULL;





		config = false;


	}

	MyApplication::~MyApplication()
	{
		delete _listener;
		//delete _root;
	}


	void MyApplication::drawcube(HandData* hd) {
		Ogre::Vector3 pos;
		for (int index=0;index<hd->FingerpointCount;index++) {
			//if (!((hd->Fingerpoints[index]->location->x<50)|(hd->Fingerpoints[index]->location->x>(640-50))|(hd->Fingerpoints[index]->location->y-480/2<50))|(hd->Fingerpoints[index]->location->y-480/2>(480-50))) {
				pos = Ogre::Vector3(hd->Fingerpoints[index]->location->x-640/2,hd->Fingerpoints[index]->location->z,hd->Fingerpoints[index]->location->y-480/2);
					
			
				if (assigned<49) {
					if (hd->Fingerpoints[index]->location->z<200) {
						if (hd->Fingerpoints[index]->location->z<20) {
							cubehold[assigned]->setScale(0.25f,0.25f,0.25f);
						}
						else
						{
							cubehold[assigned]->setScale(0.1f,0.1f,0.1f);
						}
						cubehold[assigned]->setPosition(pos);
						assigned++;
					}
				}
			//}
		}

		if (assigned<49) {
			for (int i = assigned; i<49; i++) {
				cubehold[i]->setPosition(Ogre::Vector3(-1000,0,0));
			}
		}


	}

	void MyApplication::resetcube() {
	
			for (int i = 0; i<49; i++) {
				cubehold[i]->setPosition(Ogre::Vector3(-1000,0,0));
			}
		


	}
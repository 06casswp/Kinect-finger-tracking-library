


//inputs are injected here and distributed as appropriate
#include "..\OIS\OIS.h"//

#include "CEGUI.h"
#include "inputman.h"
#include "RendererModules\Ogre\CEGUIOgreRenderer.h"







void inputz::keyevent(int type, const OIS::KeyEvent &arg) { //take the input event
	if (crazyed) {

		switch(type) {
		case 1: //key press

			sys->injectKeyDown(arg.key);
			sys->injectChar(arg.text);
			bid[arg.key].down = true;
			
			break;
		case 2: //key release
			sys->injectKeyUp(arg.key);
			bid[arg.key].pressed = bid[arg.key].pressed + bid[arg.key].down;
			bid[arg.key].down = false;
			
			break;
		default:
			break;
		}
	}
}


void inputz::mouseevent(int type, OIS::MouseButtonID id) { //take the input event
	if (crazyed) {
		switch(type) {
		case 1: //mouse click
			sys->injectMouseButtonDown(convertButton(id));
			bid[id+89].down = true;
			break;
		case 2: //mouse release
			sys->injectMouseButtonUp(convertButton(id));
			bid[id+89].pressed = bid[id+89].pressed + bid[id+89].down;
			bid[id+89].down = false;
			break;
		default:
			break;
		}
	}
}

void inputz::setmouse(int x,int y) {
	sys->injectMousePosition(x,y);


}

void inputz::mousemove(const OIS::MouseEvent &arg) { //take the input event
/*
	if (crazyed) {
		float x1;
		float y1;
		if ((X+arg.state.X.rel)>maxX-1) {
			x1 = (maxX-1-X);
			X = maxX-1;
		}
		else if ((X+arg.state.X.rel)<-maxX) {
			x1 = -maxX-X;
			X = -maxX;
		}
		else 
		{
			x1 = arg.state.X.rel;
			X = X + arg.state.X.rel;

		}
		if ((Y+arg.state.Y.rel)>maxY-1) {
			y1 = (maxY-1-Y);
			Y = maxY-1;
		}
		else if ((Y+arg.state.Y.rel)<-maxY) {
			y1 = -maxY-Y;
			Y = -maxY;
		}
		else
		{
			y1 = arg.state.Y.rel;
			Y = Y + arg.state.Y.rel;

		}		




		sys->injectMouseMove(x1, y1);

		// Scroll wheel.
		if (arg.state.Z.rel) {
			sys->injectMouseWheelChange(arg.state.Z.rel / 120.0f);
		}
	}
	else
	{
		MX += arg.state.X.rel;
		MY += arg.state.Y.rel;				;
	}
	*/
}



CEGUI::MouseButton inputz::convertButton(OIS::MouseButtonID buttonID)
{
	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;

	case OIS::MB_Right:
		return CEGUI::RightButton;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;

	default:
		return CEGUI::LeftButton;
	}
}

void inputz::reset() {
	//mouse
	MX = 0;
	MY = 0;


	//keys
	int index = 0;
	for (index= 0;index<238;index++) {
		bid[index].pressed = 0;
	}

}
void inputz::resetdown() {
	//mouse
	MX = 0;
	MY = 0;


	//keys
	int index = 0;
	for (index= 0;index<238;index++) {
		bid[index].down = false;
	}

}



inputz::inputz() {
	
	sys = NULL;
	


	crazyed = true;
	
	reset();
	resetdown();

	

	X = 0;
	Y = 0;
	maxX = 0;
	maxY = 0;

	count = 0;




}



int inputz::retrievedown(int actionid) { //for actions to check


	return bid[actionid].down;
	
}

int inputz::retrievecount(int actionid) { //for actions to check
	return bid[actionid].pressed;
}

/*to be managed here\
GUI stuff ie escape key for the menu
C key for camera change control
interface key for gui interactive controls
key for entering exiting pilot mode
switch mouse fly key

no actions are performed here, just providing the number or inputs on which keys

//to be managed in universe
ALL THINGS THAT HAVE DURATION AND TIMING CONSIDERATIONS
steering direction
thruster firing

/* OIS key code numbers:
KC_UNASSIGNED  = 0x00,0
KC_ESCAPE      = 0x01,1-
KC_1           = 0x02,2-
KC_2           = 0x03,3-
KC_3           = 0x04,4-
KC_4           = 0x05,5-
KC_5           = 0x06,6-
KC_6           = 0x07,7-
KC_7           = 0x08,8-
KC_8           = 0x09,9-
KC_9           = 0x0A,10-
KC_0           = 0x0B,11-
KC_MINUS       = 0x0C,12-    // - on main keyboard
KC_EQUALS      = 0x0D,13-
KC_BACK        = 0x0E,14-    // backspace
KC_TAB         = 0x0F,15-
KC_Q           = 0x10,16-
KC_W           = 0x11,17-
KC_E           = 0x12,18-
KC_R           = 0x13,19-
KC_T           = 0x14,20-
KC_Y           = 0x15,21-
KC_U           = 0x16,22-
KC_I           = 0x17,23-
KC_O           = 0x18,24-
KC_P           = 0x19,25-
KC_LBRACKET    = 0x1A,26-
KC_RBRACKET    = 0x1B,27-
KC_RETURN      = 0x1C,28-    // Enter on main keyboard
KC_LCONTROL    = 0x1D,29-
KC_A           = 0x1E,30-
KC_S           = 0x1F,31-
KC_D           = 0x20,32-
KC_F           = 0x21,33-
KC_G           = 0x22,34-
KC_H           = 0x23,35-
KC_J           = 0x24,36-
KC_K           = 0x25,37-
KC_L           = 0x26,38-
KC_SEMICOLON   = 0x27,39-
KC_APOSTROPHE  = 0x28,40-
KC_GRAVE       = 0x29,41-    // accent next to 1
KC_LSHIFT      = 0x2A,42-
KC_BACKSLASH   = 0x2B,43-
KC_Z           = 0x2C,44-
KC_X           = 0x2D,45-
KC_C           = 0x2E,46-
KC_V           = 0x2F,47-
KC_B           = 0x30,48-
KC_N           = 0x31,49-
KC_M           = 0x32,50-
KC_COMMA       = 0x33,51-
KC_PERIOD      = 0x34,52-    // . on main keyboard
KC_SLASH       = 0x35,53-    // / on main keyboard
KC_RSHIFT      = 0x36,54-
KC_MULTIPLY    = 0x37,55-    // * on numeric keypad
KC_LMENU       = 0x38,56-    // left Alt
KC_SPACE       = 0x39,57-
KC_CAPITAL     = 0x3A,58-
KC_F1          = 0x3B,59-
KC_F2          = 0x3C,60-
KC_F3          = 0x3D,61-
KC_F4          = 0x3E,62-
KC_F5          = 0x3F,63-
KC_F6          = 0x40,64-
KC_F7          = 0x41,65-
KC_F8          = 0x42,66-
KC_F9          = 0x43,67-
KC_F10         = 0x44,68-
KC_NUMLOCK     = 0x45,69-
KC_SCROLL      = 0x46,70-    // Scroll Lock
KC_NUMPAD7     = 0x47,71-
KC_NUMPAD8     = 0x48,72-
KC_NUMPAD9     = 0x49,73-
KC_SUBTRACT    = 0x4A,74-    // - on numeric keypad
KC_NUMPAD4     = 0x4B,75-
KC_NUMPAD5     = 0x4C,76-
KC_NUMPAD6     = 0x4D,77-
KC_ADD         = 0x4E,78-    // + on numeric keypad
KC_NUMPAD1     = 0x4F,79-
KC_NUMPAD2     = 0x50,80-
KC_NUMPAD3     = 0x51,81-
KC_NUMPAD0     = 0x52,82-
KC_DECIMAL     = 0x53,83-    // . on numeric keypad
KC_OEM_102     = 0x56,86    // < > | on UK/Germany keyboards
KC_F11         = 0x57,87-
KC_F12         = 0x58,88-
----------------------------------------------
MB_Left 89, 
MB_Right, 90
MB_Middle, 91
MB_Button3, 92
MB_Button4,	93
MB_Button5, 94
MB_Button6,	95
MB_Button7 96
----------------------------------------------

KC_F13         = 0x64,100    //                     (NEC PC98)
KC_F14         = 0x65,101    //                     (NEC PC98)
KC_F15         = 0x66,102    //                     (NEC PC98)
KC_KANA        = 0x70,112    // (Japanese keyboard)
KC_ABNT_C1     = 0x73,115    // / ? on Portugese (Brazilian) keyboards
KC_CONVERT     = 0x79,121    // (Japanese keyboard)
KC_NOCONVERT   = 0x7B,123    // (Japanese keyboard)
KC_YEN         = 0x7D,125    // (Japanese keyboard)
KC_ABNT_C2     = 0x7E,126    // Numpad . on Portugese (Brazilian) keyboards
KC_NUMPADEQUALS= 0x8D,141    // = on numeric keypad (NEC PC98)
KC_PREVTRACK   = 0x90,144    // Previous Track (KC_CIRCUMFLEX on Japanese keyboard)
KC_AT          = 0x91,145    //                     (NEC PC98)
KC_COLON       = 0x92,146    //                     (NEC PC98)
KC_UNDERLINE   = 0x93,147    //                     (NEC PC98)
KC_KANJI       = 0x94,148    // (Japanese keyboard)
KC_STOP        = 0x95,149    //                     (NEC PC98)
KC_AX          = 0x96,150    //                     (Japan AX)
KC_UNLABELED   = 0x97,151    //                        (J3100)
KC_NEXTTRACK   = 0x99,153    // Next Track
KC_NUMPADENTER = 0x9C,156-    // Enter on numeric keypad
KC_RCONTROL    = 0x9D,157-
KC_MUTE        = 0xA0,160    // Mute
KC_CALCULATOR  = 0xA1,161    // Calculator
KC_PLAYPAUSE   = 0xA2,162    // Play / Pause
KC_MEDIASTOP   = 0xA4,164    // Media Stop
KC_VOLUMEDOWN  = 0xAE,174    // Volume -
KC_VOLUMEUP    = 0xB0,176    // Volume +
KC_WEBHOME     = 0xB2,178    // Web home
KC_NUMPADCOMMA = 0xB3,179    // , on numeric keypad (NEC PC98)
KC_DIVIDE      = 0xB5,181-    // / on numeric keypad
KC_SYSRQ       = 0xB7,183-   //PRINT SCREEN
KC_RMENU       = 0xB8,184-    // right Alt
KC_PAUSE       = 0xC5,197-    // Pause
KC_HOME        = 0xC7,199-    // Home on arrow keypad
KC_UP          = 0xC8,200-    // UpArrow on arrow keypad
KC_PGUP        = 0xC9,201-    // PgUp on arrow keypad
KC_LEFT        = 0xCB,203-    // LeftArrow on arrow keypad
KC_RIGHT       = 0xCD,205-    // RightArrow on arrow keypad
KC_END         = 0xCF,207-    // End on arrow keypad
KC_DOWN        = 0xD0,208-    // DownArrow on arrow keypad
KC_PGDOWN      = 0xD1,209-    // PgDn on arrow keypad
KC_INSERT      = 0xD2,210-    // Insert on arrow keypad
KC_DELETE      = 0xD3,211-    // Delete on arrow keypad
KC_LWIN        = 0xDB,219-    // Left Windows key
KC_RWIN        = 0xDC,220-    // Right Windows key
KC_APPS        = 0xDD,221-    // AppMenu key right alt/ctrl
KC_POWER       = 0xDE,222    // System Power
KC_SLEEP       = 0xDF,223    // System Sleep
KC_WAKE        = 0xE3,227    // System Wake
KC_WEBSEARCH   = 0xE5,229    // Web Search
KC_WEBFAVORITES= 0xE6,230    // Web Favorites
KC_WEBREFRESH  = 0xE7,231    // Web Refresh
KC_WEBSTOP     = 0xE8,232    // Web Stop
KC_WEBFORWARD  = 0xE9,233    // Web Forward
KC_WEBBACK     = 0xEA,234    // Web Back
KC_MYCOMPUTER  = 0xEB,235    // My Computer
KC_MAIL        = 0xEC,236    // Mail
KC_MEDIASELECT = 0xED,237     // Media Select
*/
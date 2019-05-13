#ifndef INPUTMANAGER
#define INPUTMANAGER

class InputManager
{
	struct inputEvents
	{
		// KeyPressed					(Not active prevous frame)
		bool KeyWPressed = false;
		bool KeySPressed = false;
		bool KeyAPressed = false;
		bool KeyDPressed = false;	
		
		bool KeyUpPressed = false;
		bool KeyDownPressed = false;
		bool KeyLeftPressed = false;
		bool KeyRightPressed = false;

		bool KeyReturnPressed = false;

		// KeyDown						(Acitve until release)
		bool KeyWDown = false;
		bool KeySDown = false;
		bool KeyADown = false;
		bool KeyDDown = false;

		bool KeyUpDown = false;
		bool KeyDownDown = false;
		bool KeyLeftDown = false;
		bool KeyRightDown = false;

		bool KeyReturnDown = false;

		//KeyRelease					(Active prevous frame)
		bool KeyWRelease = false;
		bool KeySRelease = false;
		bool KeyARelease = false;
		bool KeyDRelease = false;

		bool KeyUpRelease = false;
		bool KeyDownRelease = false;
		bool KeyLeftRelease = false;
		bool KeyRightRelease = false;

		bool KeyReturnRelease = false;

		//MousePressed
		bool MouseRightClicked = false;
		bool MouseLeftClicked = false;

		//MouseDown
		bool MouseRightDown = false;
		bool MouseLeftDown = false;

		//MouseRealeased
		bool MouseRightRelease = false;
		bool MouseLeftRelease = false;
	};

private:
public:
	static void processInputEvents();
	static inputEvents input;
};

#endif // !INPUTMANAGER

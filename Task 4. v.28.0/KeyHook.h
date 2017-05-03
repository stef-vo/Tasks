#pragma once
#include "KeyList.h"

namespace Keyboard
{
	// for global keyboard hooking
	class KeyboardHooking
	{
	public:
		void StartKeyboardHooking();
		void StopKeyboardHooking();

		//to be run for low level hooking
		static LRESULT CALLBACK LowLevelKeyboardHook(int code, WPARAM wParam, LPARAM lParam);

		//the loop for getting messages
		static void MsgLoop();
	};

}
#pragma once
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <fstream>

namespace Keyboard
{
	// class for VK codes and key_names
	class KeyPair
	{
	public:
		KeyPair() {}
		KeyPair(UINT vk_code, std::string key_name) : vk(vk_code), name(key_name) {}

		// gets key name of vk key
		std::string GetKeyName();

	private:
		UINT vk;
		std::string name;
	};

	// the keys to be inspected
	// you can change the list by adding or removing keys using the table below  the lists
	
	static std::map <UINT, KeyPair> key_map =
	{
		{ 0x03, KeyPair(VK_CANCEL, "CANCEL") },
		{ 0x08, KeyPair(VK_BACK, "BACKSPACE") },
		{ 0x09, KeyPair(VK_TAB, "TAB") },
		{ 0x0C, KeyPair(VK_CLEAR, "CLEAR") },
		{ 0x0D, KeyPair(VK_RETURN, "ENTER") },
		{ 0x10, KeyPair(VK_SHIFT, "SHIFT") },
		{ 0x11, KeyPair(VK_CONTROL, "CTRL") },
		{ 0x13, KeyPair(VK_PAUSE, "PAUSE") },
		{ 0x14, KeyPair(VK_CAPITAL, "CAPSLOCK") },
		{ 0x1B, KeyPair(VK_ESCAPE, "ESCAPE") },
		{ 0x20, KeyPair(VK_SPACE, " ") },
		{ 0x21, KeyPair(VK_PRIOR, "PAGEUP") },
		{ 0x22, KeyPair(VK_NEXT, "PAGEDOWN") },
		{ 0x23, KeyPair(VK_END, "END") },
		{ 0x24, KeyPair(VK_HOME, "HOME") },
		{ 0x25, KeyPair(VK_LEFT, "LEFT") },
		{ 0x26, KeyPair(VK_UP, "UP") },
		{ 0x27, KeyPair(VK_RIGHT, "RIGHT") },
		{ 0x28, KeyPair(VK_DOWN, "DOWN") },
		{ 0x29, KeyPair(VK_SELECT, "SELECT") },
		{ 0x2A, KeyPair(VK_PRINT, "PRINT") },
		{ 0x2B, KeyPair(VK_EXECUTE, "EXECUTE") },
		{ 0x2C, KeyPair(VK_SNAPSHOT, "PRINTSCR") },
		{ 0x2D, KeyPair(VK_INSERT, "INS") },
		{ 0x2E, KeyPair(VK_DELETE, "DEL") },
		{ 0x2F, KeyPair(VK_HELP, "HELP") },
		{ 0x30, KeyPair(0x30, "0") },
		{ 0x31, KeyPair(0x31, "1") },
		{ 0x32, KeyPair(0x32, "2") },
		{ 0x33, KeyPair(0x33, "3") },
		{ 0x34, KeyPair(0x34, "4") },
		{ 0x35, KeyPair(0x35, "5") },
		{ 0x36, KeyPair(0x36, "6") },
		{ 0x37, KeyPair(0x37, "7") },
		{ 0x38, KeyPair(0x38, "8") },
		{ 0x39, KeyPair(0x39, "9") },
		{ 0x41, KeyPair(0x41, "A") },
		{ 0x42, KeyPair(0x42, "B") },
		{ 0x43, KeyPair(0x43, "C") },
		{ 0x44, KeyPair(0x44, "D") },
		{ 0x45, KeyPair(0x45, "E") },
		{ 0x46, KeyPair(0x46, "F") },
		{ 0x47, KeyPair(0x47, "G") },
		{ 0x48, KeyPair(0x48, "H") },
		{ 0x49, KeyPair(0x49, "I") },
		{ 0x4A, KeyPair(0x4A, "J") },
		{ 0x4B, KeyPair(0x4B, "K") },
		{ 0x4C, KeyPair(0x4C, "L") },
		{ 0x4D, KeyPair(0x4D, "M") },
		{ 0x4E, KeyPair(0x4E, "N") },
		{ 0x4F, KeyPair(0x4F, "O") },
		{ 0x50, KeyPair(0x50, "P") },
		{ 0x51, KeyPair(0x51, "Q") },
		{ 0x52, KeyPair(0x52, "R") },
		{ 0x53, KeyPair(0x53, "S") },
		{ 0x54, KeyPair(0x54, "T") },
		{ 0x55, KeyPair(0x55, "U") },
		{ 0x56, KeyPair(0x56, "V") },
		{ 0x57, KeyPair(0x57, "W") },
		{ 0x58, KeyPair(0x58, "X") },
		{ 0x59, KeyPair(0x59, "W") },
		{ 0x5A, KeyPair(0x5A, "Z") },
		{ 0x5B, KeyPair(VK_LWIN, "WIN") },
		{ 0x5C, KeyPair(VK_RWIN, "WIN") },
		{ 0x5D, KeyPair(VK_APPS, "APPS") },
		{ 0x5F, KeyPair(VK_SLEEP, "SLEEP") },
		{ 0x60, KeyPair(VK_NUMPAD0, "NUM0") },
		{ 0x61, KeyPair(VK_NUMPAD1, "NUM1") },
		{ 0x62, KeyPair(VK_NUMPAD2, "NUM2") },
		{ 0x63, KeyPair(VK_NUMPAD3, "NUM3") },
		{ 0x64, KeyPair(VK_NUMPAD4, "NUM4") },
		{ 0x65, KeyPair(VK_NUMPAD5, "NUM5") },
		{ 0x66, KeyPair(VK_NUMPAD6, "NUM6") },
		{ 0x67, KeyPair(VK_NUMPAD7, "NUM7") },
		{ 0x68, KeyPair(VK_NUMPAD8, "NUM8") },
		{ 0x69, KeyPair(VK_NUMPAD9, "NUM9") },
		{ 0x6A, KeyPair(VK_MULTIPLY, "NUM*") },
		{ 0x6B, KeyPair(VK_ADD, "NUM+") },
		{ 0x6C, KeyPair(VK_SEPARATOR, "NUM,") },
		{ 0x6D, KeyPair(VK_SUBTRACT, "NUM-") },
		{ 0x6E, KeyPair(VK_DECIMAL, "NUM.") },
		{ 0x6F, KeyPair(VK_DIVIDE, "NUM/") },
		{ 0x70, KeyPair(VK_F1, "F1") },
		{ 0x71, KeyPair(VK_F2, "F2") },
		{ 0x72, KeyPair(VK_F3, "F3") },
		{ 0x73, KeyPair(VK_F4, "F4") },
		{ 0x74, KeyPair(VK_F5, "F5") },
		{ 0x75, KeyPair(VK_F6, "F6") },
		{ 0x76, KeyPair(VK_F7, "F7") },
		{ 0x77, KeyPair(VK_F8, "F8") },
		{ 0x78, KeyPair(VK_F9, "F9") },
		{ 0x79, KeyPair(VK_F10, "F10") },
		{ 0x7A, KeyPair(VK_F11, "F11") },
		{ 0x7B, KeyPair(VK_F12, "F12") },
		{ 0x90, KeyPair(VK_NUMLOCK, "NUM") },
		{ 0x91, KeyPair(VK_SCROLL, "SCRLOCK") },
		{ 0xA0, KeyPair(VK_LSHIFT, "SHIFT") },
		{ 0xA1, KeyPair(VK_RSHIFT, "SHIFT") },
		{ 0xA2, KeyPair(VK_LCONTROL, "CTRL") },
		{ 0xA3, KeyPair(VK_RCONTROL, "CTRL") },
		{ 0xBA, KeyPair(VK_OEM_1, ";") },
		{ 0xBC, KeyPair(VK_OEM_COMMA, "=") },
		{ 0xBD, KeyPair(VK_OEM_MINUS, ",") },
		{ 0xBE, KeyPair(VK_OEM_PERIOD, ".") },
		{ 0xBF, KeyPair(VK_OEM_2, "/") },
		{ 0xC0, KeyPair(VK_OEM_3, "`") },
		{ 0xDB, KeyPair(VK_OEM_4, "[") },
		{ 0xDC, KeyPair(VK_OEM_5, "\\") },
		{ 0xDD, KeyPair(VK_OEM_6, "]") },
		{ 0xDE, KeyPair(VK_OEM_7, "\'") },
		{ VK_MENU, KeyPair(VK_MENU, "ALT") },
		{ VK_LMENU, KeyPair(VK_LMENU, "ALT") },
		{ VK_RMENU, KeyPair(VK_RMENU, "ALT") },
	};

}




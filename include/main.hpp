#include <Windows.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>


// from https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
#define VK_KEY_0 0x30
#define VK_KEY_1 0x31
#define VK_KEY_2 0x32
#define VK_KEY_3 0x33
#define VK_KEY_4 0x34
#define VK_KEY_5 0x35
#define VK_KEY_6 0x36
#define VK_KEY_7 0x37
#define VK_KEY_8 0x38
#define VK_KEY_9 0x39
#define VK_KEY_A 0x41
#define VK_KEY_B 0x42
#define VK_KEY_C 0x43
#define VK_KEY_D 0x44
#define VK_KEY_E 0x45
#define VK_KEY_F 0x46
#define VK_KEY_G 0x47
#define VK_KEY_H 0x48
#define VK_KEY_I 0x49
#define VK_KEY_J 0x4A
#define VK_KEY_K 0x4B
#define VK_KEY_L 0x4C
#define VK_KEY_M 0x4D
#define VK_KEY_N 0x4E
#define VK_KEY_O 0x4F
#define VK_KEY_P 0x50
#define VK_KEY_Q 0x51
#define VK_KEY_R 0x52
#define VK_KEY_S 0x53
#define VK_KEY_T 0x54
#define VK_KEY_U 0x55
#define VK_KEY_V 0x56
#define VK_KEY_W 0x57
#define VK_KEY_X 0x58
#define VK_KEY_Y 0x59
#define VK_KEY_Z 0x5A


WNDCLASSEXA windowClass;
LPCSTR CLASS_NAME = "SfgClass";

UINT_PTR ID_CONTROL_EDIT = 0x00000001;

UINT_PTR ID_MENU_FILE_NEW = 0x00001001;
UINT_PTR ID_MENU_FILE_OPEN = 0x00001002;
UINT_PTR ID_MENU_FILE_SAVE = 0x00001003;
UINT_PTR ID_MENU_FILE_SAVEAS = 0x00001004;
UINT_PTR ID_MENU_FILE_EXIT = 0x00001005;
UINT_PTR ID_MENU_EDIT_UNDO = 0x00001006;
UINT_PTR ID_MENU_EDIT_CUT = 0x00001007;
UINT_PTR ID_MENU_EDIT_COPY = 0x00001008;
UINT_PTR ID_MENU_EDIT_PASTE = 0x00001009;
UINT_PTR ID_MENU_EDIT_DELETE = 0x0000100A;
UINT_PTR ID_MENU_EDIT_SEARCHWEB = 0x0000100B;
UINT_PTR ID_MENU_EDIT_FIND = 0x0000100C;
UINT_PTR ID_MENU_EDIT_FINDNEXT = 0x0000100D;
UINT_PTR ID_MENU_EDIT_FINDPREVIOUS = 0x0000100E;
UINT_PTR ID_MENU_EDIT_REPLACE = 0x0000100F;
UINT_PTR ID_MENU_EDIT_GOTO = 0x00001010;
UINT_PTR ID_MENU_EDIT_SELECTALL = 0x00001011;
UINT_PTR ID_MENU_EDIT_TIMEDATE = 0x00001012;
UINT_PTR ID_MENU_FORMAT_WORDWRAP = 0x00001013;
UINT_PTR ID_MENU_FORMAT_FONT = 0x00001014;
UINT_PTR ID_MENU_VIEW_ZOOM_IN = 0x00001015;
UINT_PTR ID_MENU_VIEW_ZOOM_OUT = 0x00001016;
UINT_PTR ID_MENU_VIEW_ZOOM_DEFAULT = 0x00001017;
UINT_PTR ID_MENU_VIEW_STATUSBAR = 0x00001018;
UINT_PTR ID_MENU_HELP_VIEWHELP = 0x00001019;
UINT_PTR ID_MENU_HELP_SENDFEEDBACK = 0x0000101A;
UINT_PTR ID_MENU_HELP_ABOUT = 0x0000101B;

FILE* fileOut = nullptr;

// void MyLog( char const* message );
void MyLog( char const* format, ... );

void MessageBoxInfo( std::string const& title, std::string const& message );
void MessageBoxError( std::string const& title, std::string const& message );

LRESULT WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE a, PSTR b, int nCmdShow );

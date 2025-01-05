#ifndef TERMINALMANAGER_H
#define TERMINALMANAGER_H

// includes
#include <common.h>
#include <stdio.h>

#if defined(WIN32)
    #include <windows.h>
    #include <winuser.h>
    int HandleKeyEvent(WORD vkey, bool keyDown);

#elif defined (UNIX)
    #include <sys/ioctl.h>
    int HandleKeyEvent(char key);

#endif

// structs


// functions
void TerminalInitialise();
int HandleTerminalEvents();
void RefreshUI();
void SetCursorPosition(Vector2Short position);
void SetTerminalSize(Vector2Short size);

// global vars
extern Vector2Short terminalSize;
extern Vector2Short cursorPos;
extern const COORD coordZero;


#endif // TERMINALMANAGER_H
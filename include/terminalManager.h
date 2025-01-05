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
void SetCursorPosition(Vector2Int position);
void SetTerminalSize(Vector2Int size);

// global vars
extern Vector2Int terminalSize;
extern Vector2Int cursorPos;
extern const COORD coordZero;


#endif // TERMINALMANAGER_H
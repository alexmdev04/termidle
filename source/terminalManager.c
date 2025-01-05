#include <terminalManager.h>

/// Converts a COORD value into a Vector2Short value
#define COORD_to_Vector2Short *(struct s_vec2int16*)&
/// Converts a Vector2Short value into a COORD value by getting its address, casting it to COORD and dereferencing the address.
#define Vector2Short_to_COORD *(struct _COORD*)&

Vector2Short terminalSize;
Vector2Short cursorPos;
const COORD coordZero = { 0,0 };

void RefreshUI() {

}

int clamp(int value, const int min, const int max) {
    value &= -(value >= min);
    return value | ((max - value) >> 31);
}

#if defined(WIN32)

    HANDLE outputHandle;
    HANDLE inputHandle;
    INPUT_RECORD inputRecord;
    DWORD events;

    void SetCursorPosition(Vector2Short position) {
        position.x = clamp(position.x, 0, terminalSize.x);
        position.y = clamp(position.y, 0, terminalSize.y);
        cursorPos = position;
        SetConsoleCursorPosition(outputHandle, Vector2Short_to_COORD position);
    }

    void SetCurrentCursorPositionAttribute(const WORD attribute) {
        DWORD out;
        FillConsoleOutputAttribute(outputHandle, attribute, 2, Vector2Short_to_COORD cursorPos, &out);
    }

    void SetTerminalSize(const Vector2Short size) {
        terminalSize = size;
    }

    /// Handles windows virtual key code events
    int HandleKeyEvent(const WORD vkey, const bool keyDown) {
        if (keyDown) {
            // apply transformation based on directional keys
            Vector2Short pos = cursorPos;
            switch (vkey) {
                case VK_UP: {
                    pos.y--;
                    break;
                }
                case VK_DOWN: {
                    pos.y++;
                    break;
                }
                case VK_LEFT: {
                    pos.x -= 2;
                    break;
                }
                case VK_RIGHT: {
                    pos.x += 2;
                    break;
                }
                case VK_ESCAPE: {
                    return -1;
                }
                default: { break; }
            }

            // fill the space with a purple square
            SetCursorPosition(pos);
            constexpr WORD attrib = BACKGROUND_BLUE | BACKGROUND_RED;
            SetCurrentCursorPositionAttribute(attrib);
        }
        return 0;
    }

    /// Setup terminal handles, enable input, set initial terminal size
    void TerminalInitialise() {
        // get terminal handles
        outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        inputHandle = GetStdHandle(STD_INPUT_HANDLE);

        // set console mode to allow input reading
        constexpr DWORD inputMode = ENABLE_WINDOW_INPUT;
        SetConsoleMode(inputHandle, inputMode);
        //constexpr DWORD outputMode = ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
        //SetConsoleMode(outputHandle, outputMode);

        // set initial terminal size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(outputHandle, &csbi);
        terminalSize = COORD_to_Vector2Short csbi.dwSize;
        cursorPos = COORD_to_Vector2Short csbi.dwCursorPosition;
    }

    int HandleTerminalEvents() {
        ReadConsoleInput(inputHandle, &inputRecord, 1, &events);
        switch (inputRecord.EventType) {
            case WINDOW_BUFFER_SIZE_EVENT: {
                terminalSize.x = inputRecord.Event.WindowBufferSizeEvent.dwSize.X;
                terminalSize.y = inputRecord.Event.WindowBufferSizeEvent.dwSize.Y;
                RefreshUI();
                return 0;
            }
            case KEY_EVENT: {
                return HandleKeyEvent(inputRecord.Event.KeyEvent.wVirtualKeyCode, inputRecord.Event.KeyEvent.bKeyDown);
            }
            default: return 0;
        }
    }

    void DrawRect() {

    }

#elif defined (UNIX)

    void termInit() {
        printf("Unix not implemented")
        int die = 0/0;
    }

    termSize GetTerminalSize() {
        termSize ret;
        printf("Unix not implemented")
        int die = 0/0;
        return ret;
    }

#endif
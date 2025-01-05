#include <terminalManager.h>

Vector2Int terminalSize;
Vector2Int cursorPos;
const COORD coordZero = { 0,0 };

void RefreshUI() {

}

#if defined(WIN32)

    HANDLE outputHandle;
    HANDLE inputHandle;
    INPUT_RECORD inputRecord;
    DWORD events;

    void SetCursorPosition(const Vector2Int position) {
        cursorPos = position;
        const COORD coord = { position.x, position.y };
        SetConsoleCursorPosition(outputHandle, coord);
    }

    void SetCurrentCursorPositionAttribute(const WORD attribute) {
        DWORD out;
        const COORD coord = { cursorPos.x, cursorPos.y };
        FillConsoleOutputAttribute(outputHandle, attribute, 1, coord, &out);
    }

    void SetTerminalSize(const Vector2Int size) {
        terminalSize = size;
    }

    /// Handles windows virtual key code events
    int HandleKeyEvent(const WORD vkey, const bool keyDown) {
        if (keyDown) {
            // apply transformation based on directional keys
            Vector2Int pos = cursorPos;
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
                    pos.x--;
                    break;
                }
                case VK_RIGHT: {
                    pos.x++;
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
        constexpr DWORD outputMode = ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
        SetConsoleMode(outputHandle, outputMode);

        // set initial terminal size
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(outputHandle, &csbi);
        terminalSize.x = csbi.dwSize.X;
        terminalSize.y = csbi.dwSize.Y;
        cursorPos.x = csbi.dwCursorPosition.X;
        cursorPos.y = csbi.dwCursorPosition.Y;
    }

    int HandleTerminalEvents() {
        DWORD out;
        //FillConsoleOutputAttribute(outputHandle, COMMON_LVB_REVERSE_VIDEO, terminalSize.x * terminalSize.y, coordZero, &out);

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
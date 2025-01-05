#include <common.h>
#include <terminalManager.h>

int main(void) {
    TerminalInitialise();

    while (!HandleTerminalEvents()) {

    }

    system("pause");
    return 0;
}
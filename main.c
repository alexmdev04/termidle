#include <common.h>
#include <stdio.h>
#include <terminalManager.h>

int main(void) {
    TermialInitialise();

    while (!HandleTerminalEvents()) {

    }

    system("pause");
    return 0;
}
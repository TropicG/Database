#include "Program.h"

void Program::src()
{
    Command command;

    while (true) {
        command.execute();

        if (command.getCommand() == "exit") {
            break;
        }
    }
}
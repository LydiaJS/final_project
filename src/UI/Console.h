#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>
#include "PrintStream.h"
#include "../Client/Client.h"
#include "../colors.h"
#define INDENT_SIZE 5

class
Console
{
    private:
        const char *prompt;
        Client client;
        PrintStream out;
    public:
        bool loop();
        Console();
};

#endif

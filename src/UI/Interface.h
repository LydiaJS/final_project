#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include "PrintStream.h"
#include "../Client/Client.h"

class
Interface
{
    private:
        const char *prompt;
        Client client;
        PrintStream out;
        void parseCommand(char *);
    public:
        Interface();
        void loop();
};
#endif

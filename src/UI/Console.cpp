#include "Console.h"

using namespace std;

Console::Console():
    client(),
    out(cout)
{
    this -> prompt = "> ";
}

bool
Console::loop()
{
    char *line;
    bool quit = false;
    size_t count;
    this -> out << RED_FG 
                << "Welcome to the Terminal Board Browser (TBB)!"
                << RESET
                << endl;
    do
    {
        count = 0;
        line = readline(this -> prompt);
        if(!line) break;
        if(*line) add_history(line);
        if(!this -> client.parse_command(line,this -> out))
            quit = true;
        free(line);
    } while(!quit);
    return true;
}

#include "Interface.h"

Interface::Interface():
    client (),
    out(cout)
{
    this -> prompt = CYAN_FG "> " RESET;
}

void
Interface::parseCommand
(char *line)
{
    size_t arg_count;
    string *args;
    unsigned int thread;
    stringstream command;

    arg_count = 0;
    command << line;
    args = new string[3];
    while(getline(command,args[arg_count++],' '));
    if(args[0] == "goto")
    {
        if(args[1] == "thread")
            this -> client.goToThread(atoi(args[2].c_str()));
        else if(args[1] == "board")
            this -> client.goToBoard(args[2]);
        else if(args[1] == "catalog")
            this -> client.goToCatalog(args[2]);
        else if(args[1] == "page")
            this -> client.goToPage(atoi(args[2].c_str()));
        else if(args[1] == "boards")
            this -> client.goToBoardList();
        else
            cout << "You need to say where to go!"
                 << endl;
    }
    else if (args[0] == "show")
    {
        this -> client.showCurrentPage(this -> out);
        this -> client.showPage(this -> out);
    }
    else
        cout << "Commands:"
             << endl
             << "goto <thread|board|catalog>"
             << endl
             << "show"
             << endl;
    delete[] args;
}

void
Interface::loop ()
{
    char *line;
    bool quit;
    size_t count;

    quit = false;
    do
    {
        count = 0;
        line = readline(this -> prompt);
        if(!line)
            break;
        if(*line) add_history(line);
            parseCommand(line);
        free(line);
    } while(!quit);
}

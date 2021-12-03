#include "Interface.h"

Interface::Interface():
    client (),
    out(cout)
{
    // Set the prompt
    this -> prompt = GREEN_FG "> " RESET;
}

void
Interface::parseCommand
(char *line, unsigned char &flags)
{
    size_t arg_count;
    string *args;
    unsigned int thread;
    stringstream command;

    arg_count = 0;
    command << line;
    args = new string[3];
    // Split the command into arguments
    while(getline(command,args[arg_count++],' '));
    
    // Evaluate the first argument to assess the command being run
    switch(args[0].c_str()[0])
    {
        case 'g':
            if (args[0] == "goto")
            {
                if(args[2].empty())
                    goto USAGE;
                switch(args[1].c_str()[0])
                {
                    case 'b':
                        if(args[1] == "board")
                            if(args[2] == "list")
                                this -> client.goToBoardList();
                            else
                                this -> client.goToBoard(args[2]);
                        else
                            goto USAGE;
                        break;
                    case 'c':
                        if(args[1] == "catalog")
                            this -> client.goToCatalog(args[2]);
                        else
                            goto USAGE;
                        break;
                    case 'p':
                        if(args[1] == "page")
                            this -> client.goToPage(atoi(args[2].c_str()));
                        else
                            goto USAGE;
                        break;
                    case 't':
                        if(args[1] == "thread")
                            this -> client.goToThread(atoi(args[2].c_str()));
                        else
                            goto USAGE;
                        break;
                    default:
                        this -> out << RED_FG "You need to say where to go!" 
                                       RESET "\n";
                        goto USAGE;
                        break;
                }
                if(flags & 2)
                {
                    this -> client.showCurrentPage(this -> out);
                    this -> client.showPage(this -> out);
                }
            }
            else
                goto USAGE;
            break;
        case 's':
            if(args[0] == "show")
            {
                this -> client.showCurrentPage(this -> out);
                this -> client.showPage(this -> out);
            }
            else
                goto USAGE;
            break;
        case 'r':
            if (args[0] == "refresh")
                this -> client.refresh();
            else
                goto USAGE;
            break;
        case 'q':
            if (args[0] == "quit")
                flags |= 1;
            else
                goto USAGE;
            break;
        case 'a':
            if(args[0] == "autoshow")
            {
                if (args[1] == "on")
                    flags |= 2;
                else if (args[1] == "off")
                    flags ^= (flags & 2);
                else
                    goto USAGE;
            } 
            else
                goto USAGE;
            break;
        default:
        USAGE: // Help page for the program
            this -> out << RED_FG
                        << "Use: \n";

            this -> out.indent(5);
            this -> out << YELLOW_FG 
                                "The Terminal Board Browser (TBB) is a "
                                "program for navigating and browsing "
                                "chan-type image boards.\n"
                           RED_FG "Commands:\n";
            this -> out.indent(5);
            this -> out << "goto <board|catalog|thread> [board|<list>|thread]"
                            YELLOW_FG " (go to a page)\n"
                            RED_FG "show" 
                            YELLOW_FG " (display the current page)\n"
                            RED_FG "refresh"
                            YELLOW_FG 
                                " (refresh the cache for the current page)\n"
                            RED_FG "autoshow <on|off>"
                            YELLOW_FG " (set whether or to autoshow pages)\n"
                            RED_FG "help"
                            YELLOW_FG " (Show this help page)\n"
                            RED_FG "quit" 
                            YELLOW_FG " (exit the program)"
                            RESET "\n";
            this -> out.indent(-10);
            break;
    }
    delete[] args;
}

void
Interface::loop ()
{
    char *line;
    unsigned char flags; // Acts as two boolean values for autoshow and quit
    
    // The first bit is set to exit the program
    // The second bit is set to turn on autoshow 
    flags = 0b00000010;

    // Greet the user
    this -> out << YELLOW_FG "Welcome to the Terminal(ly) Board Browser!"
                   RESET "\n";

    // Start the command loop
    do
    {
        // Get the command from the user
        line = readline(this -> prompt);
        
        if(!line)
            continue;

        // If the user enters nothing, skip the rest of the loop
        if(*line)
            add_history(line);
        // Parse the entered command
        parseCommand(line, flags);

        // Free the line, as not to waste memory
        free(line);
        // quit if the user has requested to quit
    } while(! (flags & 1));
}

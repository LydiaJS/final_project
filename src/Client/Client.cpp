#include "Client.h"

using namespace std;

Client::Client():
    CM()
{
    this -> target.type = BOARD_LIST;
}

string
Client::getCurrentPage()
{
    string page;
    switch(this -> target.type)
    {
        case THREAD_LIST:
            page = this -> target.board;
            break;
        case CATALOG:
            page = "/";
            page += this -> target.board;
            page += "/ (catalog)";
            break;
        case THREAD:
            page = "/";
            page += this -> target.board;
            page += "/ (No.";
            page += this -> target.thread;
            page += ")";
            break;
        case BOARD_LIST:
            page = "board list";
            break;
    }
    return page;
}



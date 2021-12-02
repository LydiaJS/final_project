#include "Client.h"

using namespace std;

Client::Client():
    CM()
{
    this -> target.type = BOARD_LIST;
    this -> target.page = 0;
}

Json::Value
Client::getContent()
{
    Json::Value content;
    const char *content_path;
    ifstream content_stream;
    if(this -> CM.prepCache(this -> target))
    {
        content_path = this -> CM.getPath(this -> target).c_str();
        content_stream.open(content_path, std::ios::binary);
        if(content_stream.good())
        {
            content_stream >> content;
            content_stream.close();
        }
    }
    return content;
}

PrintStream&
Client::showCurrentPage
(PrintStream& ps)
{
    switch(this -> target.type)
    {
        case THREAD_LIST:
            ps << RED_FG
               << "/"
               << this -> target.board
               << "/ Page: "
               << YELLOW_FG
               << (unsigned int) this -> target.page
               << RESET;
            break;
        case CATALOG:
            ps << RED_FG
               << "/"
               << this -> target.board
               << "/ Page:" 
               << YELLOW_FG
               << this -> target.page
               << " (catalog)"
               << RESET;
            break;
        case THREAD:
            ps << RED_FG
               << "/"
               << this -> target.board
               << "/"
               << YELLOW_FG
               << " (No."
               << this -> target.thread
               << ")"
               << RESET;
            break;
        case BOARD_LIST:
            ps << RED_FG
               << "board list"
               << RESET;
            break;
    }
    ps << "\n";
    return ps;
}

PrintStream&
Client::showPage
(PrintStream &ps)
{
    string content_path;
    Json::Value content;
    unsigned int count, page;

    content = this -> getContent();
    switch(this -> target.type)
    {
        case BOARD_LIST:
            count = content["boards"].size();
            ps << YELLOW_FG;
            while(--count)
                ps <<  content["boards"][count]["board"].asString()
                   << " ";
            ps << RESET << "\n";
            break;
        case THREAD_LIST:
            page = static_cast<unsigned int>(this -> target.page);
            count = 0;
            while(count < content[page]["threads"].size())
            {
                ps << RED_FG
                   << "No."
                   << YELLOW_FG
                   << content[page]["threads"][count]["no"]
                   << RESET
                   << "\n";
                ++count;
            }
            break;
        case CATALOG:
            {
                Catalog catalog(content);
                catalog.showPage(ps,this -> target.page);
                break;
            }
        case THREAD:
            {
                Thread thread(content);
                ps << thread;
                break;
            }
        case MEDIA: 
            break;
    }
    return ps;
}

void
Client::goToBoardList()
{
    this -> target.type = BOARD_LIST;
}

void
Client::goToBoard
(string board)
{
    this -> target.type = THREAD_LIST;
    this -> target.board = board;
    this -> target.page = 0;
}

void
Client::goToCatalog
(string board)
{
    this -> target.type = CATALOG;
    this -> target.board = board;
    this -> target.page = 0;
}

void
Client::goToThread
(unsigned int thread)
{
    this -> target.type = THREAD;
    this -> target.thread = thread;
}

void
Client::goToPage
(unsigned char page)
{
    this -> target.page = page;
}

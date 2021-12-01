#include "Client.h"

using namespace std;

Client::Client():
    CM()
{
    this -> target.type = BOARD_LIST;
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

string
Client::getPage()
{
    string page_string, content_path;
    Json::Value content;
    unsigned int count, subcount;
    content = this -> getContent();
    switch(this -> target.type)
    {
        case BOARD_LIST:
            page_string = "";
            count = content["boards"].size();
            while(--count)
                page_string = content["boards"][count]["board"].asString() 
                            + "\n"
                            + page_string;
            break;
        case THREAD_LIST:
            page_string = "";
            count = content.size();
            while(--count)
            {
                subcount = content[count]["threads"].size();
                while(--subcount)
                    page_string = 
                        content[count]["threads"][subcount]["no"].asString() 
                        + "\n"
                        + page_string;
            }
            break;
        case CATALOG:
            {
                Catalog catalog(content);
                page_string = catalog.toString();
                break;
            }
        case THREAD:
            {
                Thread thread(content);
                page_string = thread.toString();
                break;
            }
        case MEDIA: 
            break;
    }
    return page_string;
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
}

void
Client::goToCatalog
(string board)
{
    this -> target.type = CATALOG;
    this -> target.board = board;
}

void
Client::goToThread
(unsigned int thread)
{
    this -> target.type = THREAD;
    this -> target.thread = thread;
}

#include "Client.h"

using namespace std;

Client::Client():
    CM()
{
    /*
     *  Initialize an instance of a Client
     */

    // Default page should be the board list
    this -> target.type = BOARD_LIST;

    // Default page number should be 0
    this -> target.page = 0;
}

Json::Value
Client::getContent()
{
    /*
     *  Read the content of the current target from cache into a Json::Value
     */

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

void
Client::refresh()
{
    /*
     *  Refresh the cache for the current page
     */
    this -> CM.setState(FORCE_REFRESH);
    this -> CM.prepCache(this -> target);
    this -> CM.setState(REFRESH);
}

PrintStream&
Client::showCurrentPage
(PrintStream& ps)
{

    /*
     *  Pass the current page PrintStream
     */

    switch(this -> target.type)
    {
        case THREAD_LIST:
            ps << RED_FG "/"
               << this -> target.board
               << "/ Page: " YELLOW_FG
               << (unsigned int) this -> target.page
               << RESET;
            break;
        case CATALOG:
            ps << RED_FG "/"
               << this -> target.board
               << "/ Page:" YELLOW_FG
               << this -> target.page
               << " (catalog)" RESET;
            break;
        case THREAD:
            ps << RED_FG "/"
               << this -> target.board
               << "/" YELLOW_FG " (No."
               << this -> target.thread
               << ")" RESET;
            break;
        case BOARD_LIST:
            ps << RED_FG "board list" RESET;
            break;
    }
    ps << "\n";
    return ps;
}

PrintStream&
Client::showPage
(PrintStream &ps)
{
    /*
     *  Pipes the current page's content to a PrintStream
     */

    string content_path;
    Json::Value content;
    unsigned int count, page;
    time_t last_modified;
    char date[20];
    struct tm *tm;
    Thread *thread;
    Catalog *catalog;

    content = this -> getContent();
    switch(this -> target.type)
    {
        case BOARD_LIST:
            count = content["boards"].size();
            ps << YELLOW_FG;
            while(--count)
                ps <<  content["boards"][count]["board"].asString()
                   << " ";
            ps << RESET "\n";
            break;
        case THREAD_LIST:
            page = static_cast<unsigned int>(this -> target.page);
            count = 0;
            ps << RED_FG "Thread No.\tReplies      Last Modified" RESET "\n";
            while(count < content[page]["threads"].size())
            {
                
                last_modified = (time_t)
                    content[page]["threads"][count]["last_modified"].asInt();
                tm = localtime(&last_modified);
                strftime(date, sizeof(date),"%F %T",tm);
                ps << YELLOW_FG
                   << content[page]["threads"][count]["no"]
                   << "\t"
                   << content[page]["threads"][count]["replies"]
                   << "\t     "
                   << date
                   << RESET "\n";
                ++count;
            }
            break;
        case CATALOG:
                catalog = new Catalog(content);
                (*catalog).showPage(ps,this -> target.page);
                delete catalog;
                break;
        case THREAD:
                thread = new Thread(content);
                ps << *thread;
                delete thread;
                break;
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
    if ( !this -> target.board.empty())
    {
        this -> target.type = THREAD;
        this -> target.thread = thread;
    }
}

void
Client::goToPage
(unsigned char page)
{
    this -> target.page = page;
}

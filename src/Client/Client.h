#ifndef __CLIENT_H__
#define __CLIENT_H__


#include "../CacheManager/CacheManager.h"
#include "../ImageBoards/OriginalPost.h"
#include "../ImageBoards/Reply.h"
#include "../ImageBoards/Thread.h"
#include "../UI/PrintStream.h"
#include "../colors.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/value.h>

class
Client
{
    private:
        CacheManager CM;
        string board;
        unsigned int thread_no;
        unsigned char page;
        void enterThread(unsigned int);
        Json::Value getContent();
    public:
        bool parse_command(const char*, PrintStream&);
        Client();
};

#endif

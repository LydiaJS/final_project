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
        Target target;
        Json::Value getContent(); 
    public:
        string currentPage();
        Client();
};

#endif

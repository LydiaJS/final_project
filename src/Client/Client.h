#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "../CacheManager/CacheManager.h"
#include "../ImageBoards/OriginalPost.h"
#include "../ImageBoards/Reply.h"
#include "../ImageBoards/Thread.h"
#include "../ImageBoards/Catalog.h"
#include "../UI/PrintStream.h"
#include "../Common/colors.h"
#include "../Common/Target.h"

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
        TargetType getCurrentTarget();
        PrintStream& showCurrentPage(PrintStream&);
        PrintStream& showPage(PrintStream&);
        void goToBoardList();
        void goToBoard(string);
        void goToCatalog(string);
        void goToThread(unsigned int);
        void goToPage(unsigned char);
        Client();
};

#endif

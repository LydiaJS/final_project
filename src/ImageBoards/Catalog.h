#ifndef __CATALOG_H__
#define __CATALOG_H__

#include "Thread.h"
#include "../UI/PrintStream.h"

#include <jsoncpp/json/json.h>
#include <ostream>
#include <string>
struct
Page
{
    unsigned char page;
    size_t thread_count;
    Thread* threads;
};

class
Catalog
{
    private:
        Page *pages;
        size_t page_count;
        Json::Value info;
    public:
        friend ostream& operator << (ostream&, const Catalog&);
        friend PrintStream& operator << (PrintStream&, const Catalog&);
        PrintStream& showPage(PrintStream&, unsigned char);
        string toString();
        Catalog();
        Catalog(const Json::Value&);
};

#endif

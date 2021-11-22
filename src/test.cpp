#include "ImageBoards/OriginalPost.h"
#include "ImageBoards/Reply.h"
#include "ImageBoards/Thread.h"
#include "ImageBoards/Catalog.h"
#include "CacheManager/CacheManager.h"
#include "UI/PrintStream.h"
#include "UI/Console.h"
#include <fstream>
#include <iostream>
#include <jsoncpp/json/value.h>
#include <string>

using namespace std;

void
testCacheManager(string board)
{
    CacheManager CM;
    const unsigned int thread = 0;
    if(CM.prepCache(board, thread))
        cout << "It should work" << endl;
    else
        cout << "Somethings wrong" << endl;
}

void
testThread(const string& board, const unsigned int thread)
{
    PrintStream out(cout);
    CacheManager CM;
    Thread test_thread;
    Json::Value content;
    string content_path;
    ifstream content_stream;
    if(CM.prepCache(board, thread))
    {
        content_path = CM.getContentPath(board, thread);
        content_stream.open(content_path.c_str(), std::ios::binary);
        if(content_stream.good())
        {
            content_stream >> content;
            test_thread = Thread(content);
            out << test_thread << endl;
            return;
        }
    }
    cout << "Something went wrong!" << endl;
}

void
testCatalog()
{
    PrintStream out(cout);
    CacheManager CM;
    Catalog test_catalog;
    Json::Value content;
    string content_path;
    ifstream content_stream;
    content_path = "testCatalog.json";
    content_stream.open(content_path.c_str(), std::ios::binary);
    if(content_stream.good())
    {
        content_stream >> content;
        test_catalog = Catalog(content);
        out << test_catalog;
        return;
    }
    cout << "Something went wrong!" << endl;
}

int
main(int argc, char **argv)
{
   Console console;
   console.loop();
   //testThread("lgbt",23241848); 
   //testCatalog();
}

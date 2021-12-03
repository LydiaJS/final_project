#include "Client/Client.h"
#include "UI/Interface.h"
#include "UI/PrintStream.h"
#include "ImageBoards/Thread.h"
#include "ImageBoards/Catalog.h"

#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>

using namespace std;


void
testClient ()
{
  PrintStream ps(cout);
  Client client;
  client.goToBoardList ();
  client.showPage (ps);
  client.goToBoard ("g");
  client.showPage (ps);
  client.goToCatalog ("g");
  client.showPage (ps);
  client.goToThread (76759434);
  client.showPage (ps);
}

void
testCatalog()
{
    PrintStream ps(cout);
    CacheManager CM;
    Json::Value content;
    string path;
    Target target;
    ifstream content_stream;
    target.type = CATALOG;
    target.board = "g";
    target.page = 0;
    CM.prepCache(target);
    path = CM.getPath(target);
    content_stream.open(path, ios::binary);
    content_stream >> content;
    
    ps << content.size() << "\n";
    ps << content[0].size() << "\n";
    ps << content[0]["threads"].size() << "\n";

    Catalog catalog(content);
    cout << catalog; 
    ps << catalog;

}


void
testThread()
{
}
void
testInterface()
{
    Interface interface;
    interface.loop();
}

int
main (int argc, char **argv)
{
  //testClient ();
  testCatalog();
  //testInterface();
}

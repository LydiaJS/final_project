#include "Client/Client.h"
#include "UI/Interface.h"
#include "UI/PrintStream.h"

#include <iostream>

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
testInterface()
{
    Interface interface;
    interface.loop();
}

int
main (int argc, char **argv)
{
  //testClient ();
  testInterface();
}

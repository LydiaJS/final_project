#include "Client/Client.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void
testClient()
{
    Client client;
    client.goToBoardList();
    cout << client.getPage();
    client.goToBoard("g");
    cout << client.getPage();
    client.goToCatalog("g");
    cout << client.getPage();
    client.goToThread(76759434);
    cout << client.getPage();
}

int
main(int argc, char **argv)
{
    testClient();
}

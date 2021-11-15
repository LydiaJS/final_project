#include "OriginalPost.h"
#include "Reply.h"
#include "CacheManager.h"
#include <fstream>
#include <iostream>
#include <jsoncpp/json/value.h>
#include <string>
void
testCacheManager()
{
    CacheManager CM;
    const string board = "g";
    const unsigned int thread = 0;
    if(CM.prepCache(board, thread))
        cout << "It should work" << endl;
    else
        cout << "Somethings wrong" << endl;
}

void
testOriginalPost()
{
    ifstream thread_file, threads_file;
    CacheManager CM;
    const string board = "g";
    const string home = getenv("HOME");
    // Sticky thread on /g/ with the most tame content managable
    unsigned int thread_no = 76759434;
    CM.prepCache(board,thread_no);
    Json::Value thread_info, threads;
    thread_file.open(home + "/" 
            + ".final_project/cache/g/thread/" 
            + to_string(thread_no) + ".json", 
            std::ios::binary);
    thread_file >> thread_info;
    thread_file.close();

    //cout << thread_info["posts"];
    OriginalPost OP(thread_info);
    cout << OP;

}

int
main(int argc, char **argv)
{
    //testCacheManager();
    testOriginalPost();
}


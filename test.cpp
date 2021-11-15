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
    unsigned int thread_no = 2;
    string thread_list_file = "/home/user/.agp2/cache/"+board+"/threads.json";
    string thread_file_path = "/home/user/.agp2/cache/"+board+"/thread/";
    CM.prepCache(board,0);

    Json::Value thread_info, threads;
    thread_file.open(thread_list_file.c_str(), 
            std::ios::binary);
    thread_file >> threads;
    thread_file.close();
    thread_no = threads[0]["threads"][3]["no"].asInt();
    CM.prepCache(board,thread_no);

    thread_file_path += to_string(thread_no) + ".json";
    thread_file.open(thread_file_path.c_str(), 
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


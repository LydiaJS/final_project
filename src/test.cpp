#include "Posts/OriginalPost.h"
#include "Posts/Reply.h"
#include "CacheManager/CacheManager.h"
#include <fstream>
#include <iostream>
#include <jsoncpp/json/value.h>
#include <string>

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
testOriginalPost(string board, unsigned int thread_no)
{
    ifstream thread_file;
    CacheManager CM;
    const string home = getenv("HOME");
    string file_path = home + "/" 
            + ".final_project/cache/"
            + board
            +"/thread/" 
            + to_string(thread_no) + ".json";
    if(CM.prepCache(board,thread_no))
        cout << "CacheManager should be working as expected" << endl;
    cout << file_path << endl;
    if(FILEEXISTS(file_path))
        cout << "Actually cached the file!" << endl;
    Json::Value thread_info;
    thread_file.open(file_path.c_str(), std::ios::binary);
    thread_file >> thread_info;
    thread_file.close();
    OriginalPost OP(thread_info);
    cout << OP;
}

int
getThreadNo(string board, unsigned int page, unsigned int thread)
{
    int thread_no;
    ifstream thread_file;
    CacheManager CM;
    const string home = getenv("HOME");
    string file_path = home + "/" 
            + ".final_project/cache/"
            + board
            +"/threads.json";
    CM.prepCache(board,0);
    Json::Value thread_info;
    thread_file.open(file_path.c_str(), std::ios::binary);
    thread_file >> thread_info;
    thread_file.close();
    thread_no = thread_info[page]["threads"][thread]["no"].asInt();
    cout << thread_no << endl;
    return thread_no;

}

int
main(int argc, char **argv)
{
    if(argc > 1)
    {
        string board = string(argv[1]);
        int page = atoi(argv[2]);
        int thread = atoi(argv[3]);
        unsigned int thread_no;
        thread_no = getThreadNo(board, page,thread);
        testOriginalPost(board,thread_no);
    }
    else
    {
        // Sticky thread on /g/ with the most tame content managable
        testCacheManager("g");
        testOriginalPost("g",76759434);
    }
    //testCacheManager();
}

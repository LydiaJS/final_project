#include "Catalog.h"
#include <iostream>

using namespace std;

Catalog::Catalog()
{
    this -> pages = NULL;
}

Catalog::Catalog(const Json::Value& content)
{
    int count, subcount, deepcount, page_count, thread_count, reply_count;
    Page *pagePtr, *lastPage;
    Thread *threadPtr, *lastThread;

    Json::Value page_content, thread_content, preview_content;

    page_count = content.size();
    this -> pages = new Page[page_count];
    pagePtr = this -> pages;
    lastPage = pagePtr + page_count;
    count = 0;
    while(pagePtr != lastPage)
    {
        subcount = 0;
        page_content = content[count];
        thread_count = page_content["threads"].size();
        pagePtr -> page = static_cast<unsigned char>(count + 1);
        pagePtr -> threads = new Thread[thread_count];
        pagePtr -> thread_count = thread_count;
        threadPtr = pagePtr -> threads;
        lastThread = threadPtr + thread_count;
        while(threadPtr != lastThread)
        {
            deepcount = 0;
            thread_content = page_content["threads"][subcount];
            reply_count = thread_content["last_replies"].size();
            preview_content["posts"][0] = thread_content;
            preview_content["posts"][0].removeMember("last_replies");
            while(deepcount < reply_count)
            {
                preview_content["posts"].append(
                        thread_content["last_replies"][deepcount]);
                ++deepcount;
            }
            *threadPtr = Thread(preview_content);
            ++subcount;
            ++threadPtr;
        }
        ++count;
        ++pagePtr;
    }
    this -> page_count = page_count;
}

ostream&
operator << (ostream& os, const Catalog& cat)
{
    size_t count, subcount;
    os << cat.page_count << "\n";
    for(count = 0; count < cat.page_count; count++)
    {
        os << "Page: " + to_string(cat.pages[count].page) + "\n";
        for(subcount = 0;subcount < cat.pages[count].thread_count;subcount++)
        {
            os << cat.pages[count].threads[subcount];
        }
    }
    return os;
}


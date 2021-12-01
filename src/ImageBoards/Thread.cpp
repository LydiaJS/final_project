#include "Thread.h"

#include <iostream>

using namespace std;

Thread::Thread()
{
    this -> num_replies = 0;
    this -> replies = NULL;
}

Thread::Thread(const Json::Value& content):
    OP(content["posts"][0])
{
    int reply_count;
    reply_count = content["posts"].size() - 1;
    this -> num_replies = static_cast<size_t>(reply_count);
    this -> replies = new Reply[reply_count];
    while(--reply_count)
        replies[reply_count] = Reply(content["posts"][reply_count + 1]);
}

OriginalPost
Thread::getOP()
{
    return this -> OP;
}

Reply*
Thread::getReplies(size_t &reply_count)
{
    reply_count = this -> num_replies;
    return this -> replies;
}

ostream&
operator << (ostream& os, const Thread& thread)
{
    Reply *replyPtr, *lastReply;
    replyPtr = thread.replies;
    lastReply = thread.replies + thread.num_replies;
    os << thread.OP;
    while(replyPtr != lastReply)
        os << *replyPtr++;
    return os;
}

#ifndef __REPLY_H__
#define __REPLY_H__

#include "Post.h"
using namespace std;
class OriginalPost;

class
Reply:
    public Post
{
    private:
    public:
        Reply();
        Reply(const Json::Value&);
};

#endif

#ifndef __REPLY_H__
#define __REPLY_H__

#include "Post.h"
#include "colors.h"
using namespace std;
class OriginalPost;

class
Reply:
    public Post
{
    private:
        friend OriginalPost;
        OriginalPost const *OP;
    public:
        friend ostream& operator << (ostream&, const Reply&);
        Reply();
        Reply(const Json::Value&);
        Reply(const OriginalPost&);
        Reply(const Json::Value&, const OriginalPost&);
        OriginalPost const *getOP();
};

#endif

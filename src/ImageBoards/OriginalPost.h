#ifndef __ORIGINAL_POST_H__
#define __ORIGINAL_POST_H__

#include "Post.h"
#include "Reply.h"

using namespace std;

class
OriginalPost:
    public Post
{
    private:
    public:
        friend ostream& operator << (ostream&, const OriginalPost&);
        string toString();
        OriginalPost();
        OriginalPost(const Json::Value&);
};

#endif

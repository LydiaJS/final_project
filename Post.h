#ifndef __POST_H__
#define __POST_H__

#include <string>
#include <ostream>
#include <jsoncpp/json/json.h>

using namespace std;

class
Post
{
    protected:
        Json::Value info;
        bool empty;
    public:
        friend ostream& operator << (ostream&, const Post&);
        Post();
        Post(const Json::Value&);
};

#endif
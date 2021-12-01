#ifndef __POST_H__
#define __POST_H__

#include <string>
#include <ostream>
#include <jsoncpp/json/json.h>
#include "../Common/colors.h"

using namespace std;

class
Post
{
    protected:
        Json::Value info;
    public:
        friend ostream& operator << (ostream&, const Post&);
        string toString();
        Post();
        Post(const Json::Value&);
};

#endif

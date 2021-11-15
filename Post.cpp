#include "Post.h"

Post::Post()
{
    this -> empty = true;
}

Post::Post(const Json::Value& in_info)
{
    this -> info = in_info;
    this -> empty = false;
}

ostream&
operator << (ostream& os, const Post& post)
{
    os << "No. " << post.info["no"] << endl;
    os << "Name: " << post.info["name"].asString() << endl;
    os << "Posted: " << post.info["now"].asString() << endl;
    if( post.info.isMember("trip"))
        os << "Tripcode: " << post.info["trip"].asString() << endl;
    if( post.info.isMember("com"))
        os << "Comment: " << post.info["com"].asString() << endl;
    return os;
}

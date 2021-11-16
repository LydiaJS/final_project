#include "Post.h"

Post::Post()
{
    this -> empty = true;
    this -> colorize = true;
    this -> default_color = WHITE_FG;
}

Post::Post(const Json::Value& in_info)
{
    this -> info = in_info;
    this -> empty = false;
    this -> colorize = true;
    this -> default_color = WHITE_FG;
}

ostream&
operator << (ostream& os, const Post& post)
{
    string no,
           name,
           now,
           trip,
           com;
    no = "No. ";
    name = "Name: " ;
    now = "Posted: ";
    trip = "Tripcode: ";
    com = "Comment ";

    if(post.colorize)
    {
        no = RED_FG + no + post.default_color;
        name = RED_FG + name + post.default_color;
        now = RED_FG + now + post.default_color;
        trip = RED_FG + trip + post.default_color;
        com = RED_FG + com + post.default_color;
    }
    os << no << post.info["no"] << endl;
    os << name << post.info["name"].asString() << endl;
    os << now << post.info["now"].asString() << endl;
    if( post.info.isMember("trip"))
        os << trip << post.info["trip"].asString() << endl;
    if( post.info.isMember("com"))
        os << com << post.info["com"].asString() << endl;
    return os;
}

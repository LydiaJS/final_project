#include "Reply.h"

Reply::Reply():
    Post()
{
    this -> OP = NULL;
    this -> default_color = GREEN_FG;
}

Reply::Reply(const Json::Value& in_info):
    Post(in_info)
{
    this -> default_color = GREEN_FG;
    this -> OP = NULL;
}

Reply::Reply(const OriginalPost& in_OP):
    Post()
{
    this -> default_color = GREEN_FG;
    this -> OP = &in_OP;
}

Reply::Reply(const Json::Value& in_info, const OriginalPost& in_OP):
    Post(in_info)
{
    this -> default_color = GREEN_FG;
    this -> OP = &in_OP;
}

OriginalPost const*
Reply::getOP()
{
    return this -> OP;
}

ostream&
operator <<(ostream& os, const Reply& reply)
{
    os << (Post) reply;
    return os;
}

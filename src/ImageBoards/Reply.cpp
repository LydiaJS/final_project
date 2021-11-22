#include "Reply.h"

Reply::Reply():
    Post(){}

Reply::Reply(const Json::Value& in_info):
    Post(in_info){}

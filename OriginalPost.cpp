#include "OriginalPost.h"

OriginalPost::OriginalPost():
    Post::Post()
{
    this -> replies = NULL;
    this -> format = true;
    this -> split_replies = true;
    this -> indent_replies = true;
    this -> minimal = false;
    this -> colorize = true;
    this -> border_pattern = DEFAULT_BORDER;
}

OriginalPost::OriginalPost(const Json::Value& in_info):
    Post::Post(in_info["posts"][0])
{
    int reply_count, count;
    this -> minimal = false;
    this -> format = true;
    this -> split_replies = true;
    this -> indent_replies = true;
    this -> colorize = true;
    this -> border_pattern = DEFAULT_BORDER;
    reply_count = this -> info["replies"].asInt();
    this -> replies = new Reply[reply_count];
    for(count = 0; count < reply_count; count++)
        this -> replies[count] = Reply(in_info["posts"][count + 1]);
}

OriginalPost::OriginalPost(const Json::Value& in_info, bool in_minimal):
    Post::Post(in_info["posts"][0])
{
    this -> replies = NULL;
    this -> format = true;
    this -> split_replies = true;
    this -> indent_replies = true;
    this -> minimal = true;
    this -> colorize = true;
    this -> border_pattern = DEFAULT_BORDER;
}

Reply *
OriginalPost::getReplies(size_t &size)
{
    size = this -> info["replies"].asInt();
    return this -> replies;
}

void
OriginalPost::setFormat(bool in_format)
{
    this -> format = in_format;
}

void
OriginalPost::setColorize(bool in_colorize)
{
    this -> colorize = in_colorize;
}

void
OriginalPost::setSplitReplies(bool in_split_replies)
{
    this -> split_replies = in_split_replies;
}

void
OriginalPost::setIndentReplies(bool in_indent_replies)
{
    this -> indent_replies = in_indent_replies;
}

void
OriginalPost::setBorderPattern(string in_border_pattern)
{
    this -> border_pattern = in_border_pattern;
}

bool
OriginalPost::toggleFormat()
{
    this -> format = ! this -> format;
    return this -> format;
}

bool
OriginalPost::toggleColorize()
{
    this -> colorize = ! this -> colorize;
    return this -> colorize;
}

bool
OriginalPost::toggleSplitReplies()
{
    this -> split_replies = ! this -> split_replies;
    return this -> split_replies;
}

bool
OriginalPost::toggleIndentReplies()
{
    this -> indent_replies = ! this -> indent_replies;
    return this -> indent_replies;
}

ostream&
operator << (ostream& os, const OriginalPost& OP)
{
    size_t count, reply_count;
    PostStream out(os);

    if(OP.colorize)
        out << YELLOW_FG;

    out << "No. " << OP.info["no"] << endl;
    out << "Name: " << OP.info["name"].asString() << endl;
    out << "Posted" <<  OP.info["now"].asString() << endl;

    if( OP.info.isMember("trip"))
        out << "Tripcode: " << OP.info["trip"].asString() << endl;
    if( OP.info.isMember("sub"))
        out << "Subject:" << OP.info["sub"].asString() << endl;
    if( OP.info.isMember("com"))
        out << "Comment: " << OP.info["com"].asString() << endl;
    reply_count = OP.info["replies"].asInt();
    out << reply_count << " replies/" 
        << OP.info["images"] << " Images" << endl;
    if (OP.colorize)
        out << GREEN_FG;
    if(OP.indent_replies)
        out.indent(5);
    for(count = 0; count < reply_count; count++)
    {
        out << OP.replies[count];
        out << endl;
    }
    if(OP.colorize)
        out << RESET;
    return os;
}

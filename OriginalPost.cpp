#include "OriginalPost.h"

OriginalPost::OriginalPost():
    Post::Post()
{
    this -> replies = NULL;
    this -> format = true;
    this -> split_replies = true;
    this -> indent_replies = true;
    this -> minimal = false;
    this -> default_color = YELLOW_FG;
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
    this -> border_pattern = DEFAULT_BORDER;
    reply_count = this -> info["replies"].asInt();
    this -> replies = new Reply[reply_count];
    for(count = 0; count < reply_count; count++)
    {
        this -> replies[count] = Reply(in_info["posts"][count + 1]);
        replies[count].colorize = this -> colorize;
    }
}

OriginalPost::OriginalPost(const Json::Value& in_info, bool in_minimal):
    Post::Post(in_info["posts"][0])
{
    this -> replies = NULL;
    this -> format = true;
    this -> split_replies = true;
    this -> indent_replies = true;
    this -> minimal = true;
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

bool
OriginalPost::isColorized()
{
    return this -> colorize;
}

ostream&
operator << (ostream& os, const OriginalPost& OP)
{
    size_t count, reply_count, reps;
    PostStream out(os);
    string border;

    out.indent(0);
    border = "";
    reply_count = OP.info["replies"].asInt();
    if(OP.colorize)
    {
        out << RED_FG 
            << "No. "  
            << YELLOW_FG
            << OP.info["no"] 
            << endl;
        out << RED_FG 
            << "Name: " 
            << YELLOW_FG
            << OP.info["name"].asString() 
            << endl;
        out << RED_FG 
            << "Posted: " 
            << YELLOW_FG
            <<  OP.info["now"].asString() 
            << endl;
        if( OP.info.isMember("trip"))
            out << RED_FG 
                << "Tripcode: " 
                << YELLOW_FG
                << OP.info["trip"].asString() 
                << endl;     
        if( OP.info.isMember("sub"))
            out << RED_FG 
                << "Subject:" 
                << YELLOW_FG
                << OP.info["sub"].asString() 
                << endl;
        if( OP.info.isMember("com"))
            out << RED_FG 
                <<"Comment: " 
                << YELLOW_FG
                << OP.info["com"].asString() 
                << endl;
        out << YELLOW_FG 
            << reply_count 
            << RED_FG 
            <<" Replies/" 
            << YELLOW_FG 
            << OP.info["images"] 
            << RED_FG 
            << " Images"
            << RESET;
    }else{
        out << "No. " << OP.info["no"] << endl;
        out << "Name: " << OP.info["name"].asString() << endl;
        out << "Posted: " <<  OP.info["now"].asString() << endl;
        if( OP.info.isMember("trip"))
            out << "Tripcode: " << OP.info["trip"].asString() << endl;
        if( OP.info.isMember("sub"))
            out << "Subject:" << OP.info["sub"].asString() << endl;
        if( OP.info.isMember("com"))
            out <<"Comment: " << OP.info["com"].asString() << endl;
        out << reply_count << " Replies/" << OP.info["images"] << " Images";
    }
    
    out << endl;

    if(OP.indent_replies)
        out.indent(INDENT_SIZE);

    if(OP.split_replies)
    {
        reps = out.getPostBuf().width/ OP.border_pattern.length();
        for(count = 0; count < reps; count++)
            border += OP.border_pattern;
    }

    for(count = 0; count < reply_count; count++)
    {
        out << border << endl;
        out << OP.replies[count];
        out << RESET << endl;
    }

    if(OP.colorize)
        out << RESET;

    return os;
}

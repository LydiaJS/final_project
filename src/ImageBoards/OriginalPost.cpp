#include "OriginalPost.h"

OriginalPost::OriginalPost():
    Post::Post(){}

OriginalPost::OriginalPost(const Json::Value& in_info):
    Post::Post(in_info){}

string
OriginalPost::toString()
{
    string OP_string;
    size_t count;
    string fields[7] = {"No. ", "Name: ", "Posted: ",
                        "Tripcode: ","Subject: ", "Attatched file: ",
                        "Comment: "};
    string keys[7] = {"no","name","now",
                      "trip","sub","filename","com"};
    OP_string = "";
    for(count = 0; count < 7; ++count)
        if(this -> info.isMember(keys[count]))
            if(keys[count] == "filename")
            {
                 OP_string += this -> info[keys[count]].asString()
                           + this -> info["ext"].asString()
                           + "\n";
            }
            else
            {
                OP_string += fields[count] 
                    + this -> info[keys[count]].asString()
                    +  '\n';
            }
    OP_string += this -> info["replies"].asString() 
        + " Replies/" 
        + this -> info["images"].asString() 
        + " Images\n"; 
    return OP_string;

}

ostream&
operator << (ostream& os, const OriginalPost& OP)
{
    size_t count;
    string fields[7] = {"No. ", "Name: ", "Posted: ",
                        "Tripcode: ","Subject: ", "Attatched file: ",
                        "Comment: "};
    string keys[7] = {"no","name","now",
                      "trip","sub","filename","com"};
    for(count = 0; count < 7; ++count)
        if(OP.info.isMember(keys[count]))
            if(keys[count] == "filename")
            {
                 os << OP.info[keys[count]].asString()
                    << OP.info["ext"].asString()
                    << "\n" RESET;
            }
            else
                os << RED_FG
                   << fields[count]
                   << YELLOW_FG 
                   << OP.info[keys[count]].asString()
                   << "\n" RESET;

    os << YELLOW_FG
       << OP.info["replies"].asString()
       << RED_FG " Replies/" YELLOW_FG 
       << OP.info["images"].asString() 
       << RED_FG " Images\n" RESET;
    return os;
}

PrintStream&
operator << (PrintStream& ps, const OriginalPost& OP)
{
    unsigned char count;
    string fields[7] = {"No. ", "Name: ", "Posted: ",
                        "Tripcode: ","Subject: ", "Attatched file: ",
                        "Comment: "};
    string keys[7] = {"no","name","now",
                      "trip","sub", "filename", "com"};
    for(count = 0; count < 7; ++count)
        if(OP.info.isMember(keys[count]))
        {
            ps << RED_FG
               << fields[count]
               << YELLOW_FG;
            if(keys[count] == "com")
            {
                ps << '\n';
                ps.indent(5);
                ps << OP.info[keys[count]].asString()
                   << "\n" RESET;
                ps.indent(-5);
            }
            else if(keys[count] == "filename")
            {
                 ps << OP.info[keys[count]].asString()
                    << OP.info["ext"].asString()
                    << "\n" RESET;
            }
            else
            {
                 ps << OP.info[keys[count]].asString()
                    << "\n" RESET;
            }
        }

    ps << YELLOW_FG
       << OP.info["replies"].asString() 
       << RED_FG " Replies/" YELLOW_FG
       << OP.info["images"].asString()
       << RED_FG " Images\n" RESET;
    return ps;
}



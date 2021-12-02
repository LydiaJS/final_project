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
    string fields[6] = {"No. ", "Name: ", "Posted: ",
                        "Tripcode: ","Subject: ", "Comment: "};
    string keys[6] = {"no","name","now",
                      "trip","sub","com"};
    OP_string = "";
    for(count = 0; count < 6; count++)
        if(this -> info.isMember(keys[count]))
            OP_string += fields[count] 
                + this -> info[keys[count]].asString()
                +  '\n';

    OP_string += this -> info["replies"].asString() 
        + " Replies/" 
        + this -> info["images"].asString() 
        + " Images" 
        + '\n' ;
    return OP_string;

}

ostream&
operator << (ostream& os, const OriginalPost& OP)
{
    size_t count;
    string fields[6] = {"No. ", "Name: ", "Posted: ",
                        "Tripcode: ","Subject: ", "Comment: "};
    string keys[6] = {"no","name","now",
                      "trip","sub","com"};
    for(count = 0; count < 6; count++)
        if(OP.info.isMember(keys[count]))
            os << RED_FG + 
                  fields[count] + 
                  YELLOW_FG + 
                  OP.info[keys[count]].asString() +
                  RESET + 
                  '\n';

    os << YELLOW_FG + 
          OP.info["replies"].asString() + 
          RED_FG + 
          " Replies/" +
          YELLOW_FG +
          OP.info["images"].asString() + 
          RED_FG +
          " Images" +
          RESET +
          '\n' ;
    return os;
}

PrintStream&
operator << (PrintStream& ps, const OriginalPost& OP)
{
    size_t count;
    string fields[6] = {"No. ", "Name: ", "Posted: ",
                        "Tripcode: ","Subject: ", "Comment: "};
    string keys[6] = {"no","name","now",
                      "trip","sub","com"};
    for(count = 0; count < 6; count++)
        if(OP.info.isMember(keys[count]))
        {
            ps << RED_FG + 
                  fields[count] + 
                  YELLOW_FG;
            if(keys[count] == "com")
            {
                ps << '\n';
                ps.indent(5);
                ps << OP.info[keys[count]].asString() +
                    RESET + 
                    '\n';
                ps.indent(-5);
            }
            else
            {
                 ps << OP.info[keys[count]].asString() +
                    RESET + 
                    '\n';
            }
        }

    ps << YELLOW_FG + 
          OP.info["replies"].asString() + 
          RED_FG + 
          " Replies/" +
          YELLOW_FG +
          OP.info["images"].asString() + 
          RED_FG +
          " Images" +
          RESET +
          '\n' ;
    return ps;
}



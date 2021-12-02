#include "Post.h"

Post::Post()
{}

Post::Post(const Json::Value& in_info)
{
    this -> info = in_info;
}

ostream&
operator << (ostream& os, const Post& post)
{
    size_t count;
    string fields[5] = {"No. ","Name: ","Posted: ","Tripcode: ","Comment: "};
    string keys[5] = {"no","name","now","trip","com"};
    for(count = 0; count < 5; count++)
        if(post.info.isMember(keys[count]))
            os << RED_FG + fields[count] + 
                  GREEN_FG + post.info[keys[count]].asString() +
                  RESET + "\n";
    return os;
}

PrintStream&
operator << (PrintStream& ps, const Post& post)
{
    size_t count;
    string fields[5] = {"No. ","Name: ","Posted: ","Tripcode: ","Comment: "};
    string keys[5] = {"no","name","now","trip","com"};
    for(count = 0; count < 5; count++)
        if(post.info.isMember(keys[count]))
        {
            ps << RED_FG 
               << fields[count]
               << GREEN_FG;
            if(keys[count] == "com")
            {
                ps << "\n";
                ps.indent(5);
                ps << post.info[keys[count]].asString()
               << RESET
               << "\n";
               ps.indent(-5);
            }
            else
            {
                ps << post.info[keys[count]].asString()
                    << RESET
                    << "\n";
            }
        }
    return ps;
}

string
Post::toString()
{
    string post_string = "";
    size_t count;
    string fields[5] = {"No. ","Name: ","Posted: ","Tripcode: ","Comment: "};
    string keys[5] = {"no","name","now","trip","com"};
    for(count = 0; count < 5; count++)
        if(this -> info.isMember(keys[count]))
            post_string +=  fields[count]
                        + this -> info[keys[count]].asString()
                        + "\n";
    return post_string;

}

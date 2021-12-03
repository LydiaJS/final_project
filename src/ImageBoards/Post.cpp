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
    unsigned char count;
    string fields[6] = {"No. ","Name: ","Posted: ",
                        "Tripcode: ","Attatched file: ","Comment: "};
    string keys[6] = {"no","name","now","trip","filename","com"};
    for(count = 0; count < 6; ++count)
        if(post.info.isMember(keys[count]))
        {
            if (keys[count] == "filename")
            {
                os << post.info[keys[count]].asString()
                   << post.info["ext"].asString()
                   << RESET "\n";
            } else {
                os << RED_FG 
                   << fields[count]
                   << GREEN_FG
                   << post.info[keys[count]].asString()
                   << RESET "\n";
            }
        }
    return os;
}

PrintStream&
operator << (PrintStream& ps, const Post& post)
{
    unsigned char count;
    string fields[6] = {"No. ","Name: ","Posted: ",
                        "Tripcode: ", "Attatched file: ","Comment: "};
    string keys[6] = {"no","name","now","trip","filename","com"};
    for(count = 0; count < 6; ++count)
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
                   << RESET "\n";
               ps.indent(-5);
            }
            else if (keys[count] == "filename")
            {
                ps << post.info[keys[count]].asString()
                   << post.info["ext"].asString()
                   << RESET "\n";
            }
            else
            {
                ps << post.info[keys[count]].asString()
                    << RESET "\n";
            }
        }
    return ps;
}

string
Post::toString()
{
    string post_string = "";
    unsigned char count;
    string fields[6] = {"No. ","Name: ","Posted: ",
                        "Tripcode: ", "Attatched file: ","Comment: "};
    string keys[6] = {"no","name","now","trip","filename","com"};
    for(count = 0; count < 6; ++count)
        if(this -> info.isMember(keys[count]))
            if( keys[count] == "filename" )
            {
                post_string +=  fields[count]
                            + this -> info[keys[count]].asString()
                            + this -> info["ext"].asString()
                            + "\n";

            }
            else
                post_string +=  fields[count]
                            + this -> info[keys[count]].asString()
                            + "\n";
    return post_string;

}

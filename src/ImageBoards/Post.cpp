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

string
Post::toString()
{
    string post_string = "";
    size_t count;
    string fields[5] = {"No. ","Name: ","Posted: ","Tripcode: ","Comment: "};
    string keys[5] = {"no","name","now","trip","com"};
    for(count = 0; count < 5; count++)
        if(this -> info.isMember(keys[count]))
            post_string += RED_FG + fields[count]
                        + GREEN_FG + this -> info[keys[count]].asString()
                        + RESET 
                        + "\n";
    return post_string;

}

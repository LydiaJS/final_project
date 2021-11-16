#ifndef __ORIGINAL_POST_H__
#define __ORIGINAL_POST_H__

#include "Post.h"
#include "Reply.h"
#include "colors.h"
#include "PostStream.h"
#define DEFAULT_BORDER "~"
#define INDENT_SIZE 5

using namespace std;

class
OriginalPost:
    public Post
{
    private:
        friend Reply;
        bool format,
             split_replies,
             indent_replies,
             minimal;
        string border_pattern;
        Reply* replies;
        friend ostream& operator << (ostream&, const Post&);
    public:
        friend ostream& operator << (ostream&, const OriginalPost&);
        OriginalPost();
        OriginalPost(const Json::Value&);
        OriginalPost(const Json::Value&,bool);
        Reply *getReplies(size_t&);
        bool isColorized();
        void setFormat(bool);
        void setColorize(bool);
        void setSplitReplies(bool);
        void setIndentReplies(bool);
        void setBorderPattern(string);
        bool toggleFormat();
        bool toggleColorize();
        bool toggleSplitReplies();
        bool toggleIndentReplies();
};

#endif

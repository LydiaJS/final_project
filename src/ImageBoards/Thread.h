#ifndef __THREAD_H__
#define __THREAD_H__

#include <fstream>
#include <jsoncpp/json/json.h>
#include "../UI/PrintStream.h"
#include "OriginalPost.h"
#include "Reply.h"

class
Thread
{
    private:
        OriginalPost OP;
        Reply *replies;
        size_t num_replies;
    public:
        friend ostream& operator<< (ostream&, const Thread&);
        friend PrintStream& operator<< (PrintStream&, const Thread&);
        string toString();
        Thread();
        ~Thread();
        Thread(const Json::Value&);
        OriginalPost getOP();
        Reply *getReplies(size_t &);
};

#endif

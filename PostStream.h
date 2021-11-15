#ifndef __POST_STREAM_H__
#define __POST_STREAM_H__

#include "PostBuf.h"

#include <iostream>
#include <iomanip>
#include <streambuf>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

class
PostStream:
    public std::ostream
{
    PostBuf buf;
    public:
        PostStream(size_t, std::ostream&);
        PostStream(std::ostream&);
        PostStream& indent(int);
    private:
        static int getWindowSize();
        static int window_size;

};

#endif

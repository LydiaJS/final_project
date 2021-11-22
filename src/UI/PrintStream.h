#ifndef __PRINT_STREAM_H__
#define __PRINT_STREAM_H__

#include "PrintBuf.h"

#include <iostream>
#include <iomanip>
#include <streambuf>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

class
PrintStream:
    public std::ostream
{
    PrintBuf buf;
    public:
        PrintStream(size_t, std::ostream&);
        PrintStream(std::ostream&);
        PrintStream& indent(int);
        PrintBuf& getPrintBuf();
    private:
        static int getWindowSize();
        static int window_size;

};

#endif

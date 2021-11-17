#ifndef __POSTBUF_H__
#define __POSTBUF_H__

#include <iostream>
#include <iomanip>
#include <streambuf>

class
PostBuf:
    public std::streambuf
{
    private:
        typedef std::basic_string<char_type> string;
        int_type overflow(int_type);
    public:
        PostBuf(int,std::streambuf*);
        ~PostBuf();
        void set_indent(int);
    
    size_t indent_width,
           width,
           def_width,
           count,
           tab_count;
    static const int tab_width = 8;
    std::string prefix;
    std::streambuf* sbuf;
    string buffer;
};

#endif

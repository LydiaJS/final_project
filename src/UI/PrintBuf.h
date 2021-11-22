#ifndef __PRINTBUF_H__
#define __PRINTBUF_H__

#include <iostream>
#include <iomanip>
#include <streambuf>

class
PrintBuf:
    public std::streambuf
{
    private:
        typedef std::basic_string<char_type> string;
        int_type overflow(int_type);
    public:
        PrintBuf(int,std::streambuf*);
        ~PrintBuf();
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

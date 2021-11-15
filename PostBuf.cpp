#include "PostBuf.h"

PostBuf::PostBuf(int w, std::streambuf* s):
    indent_width(0),
    def_width(w),
    width(w),
    sbuf(s),
    count(0)
{}

PostBuf::~PostBuf()
{
    overflow('\n');
}

void
PostBuf::set_indent(int w)
{
    if (w == 0)
    {
        this -> prefix.clear();
        this -> indent_width = 0;
        this -> width = this -> def_width;
    }
    else
    {
        this -> indent_width += w;
        this -> prefix = std::string(this -> indent_width,' ');
        this -> width -= w;
    }
}

PostBuf::int_type
PostBuf::overflow(int_type c)
{
    if(traits_type::eq_int_type(traits_type::eof(),c))
        return traits_type::not_eof(c);
    switch (c)
    {
        case '\n':
        case '\r':
            {
            this -> buffer += c;
            this -> count = 0;
            this -> sbuf -> 
                sputn(this -> prefix.c_str(), this -> indent_width);
            int_type rc = this -> sbuf -> 
                sputn(this -> buffer.c_str(), this -> buffer.size());
            this -> buffer.clear();
            return rc;
            }
        case '\a':
            return this -> sbuf -> sputc(c);
        case '\t':
            this -> buffer += c;
            this -> count += 
                this -> tab_width - 
                this -> count %
                this -> tab_width;
            return c;
        default:
            if ( this -> count >= this -> width)
            {
                size_t wpos = this -> buffer.find_last_of(" \t");
                if(wpos != string::npos)
                {
                    this -> sbuf -> sputn(
                            this -> prefix.c_str(),
                            this -> indent_width);
                    this -> sbuf -> sputn(
                            this -> buffer.c_str(),
                            wpos);
                    this -> count = this -> buffer.size() - wpos - 1;
                    this -> buffer = string(this -> buffer, wpos + 1);
                }
                else
                {
                    this -> sbuf -> sputn(
                            this -> prefix.c_str(),
                            this -> indent_width);
                     this -> sbuf -> sputn(
                            this -> buffer.c_str(),
                            this -> buffer.size());
                     this -> buffer.clear();
                     this -> count = 0;
                }
                this -> sbuf -> sputc('\n');
            }
            this -> buffer += c;
            ++(this -> count);
            return c;
    }
}


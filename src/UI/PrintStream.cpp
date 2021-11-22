#include "PrintStream.h"

PrintStream::PrintStream(size_t width, std::ostream &os):
    buf(width, os.rdbuf()),
    std::ostream(&buf)
{}

PrintStream::PrintStream(std::ostream &os):
    buf(this -> window_size, os.rdbuf()),
    std::ostream(&buf)
{}

int
PrintStream::getWindowSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int
PrintStream::window_size { getWindowSize() };

PrintStream&
PrintStream::indent(int w)
{
    this -> buf.set_indent(w);
    return *this;
}

PrintBuf&
PrintStream::getPrintBuf()
{
    return this -> buf;
}

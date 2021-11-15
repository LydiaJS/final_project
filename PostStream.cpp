#include "PostStream.h"

PostStream::PostStream(size_t width, std::ostream &os):
    buf(width, os.rdbuf()),
    std::ostream(&buf)
{}

int
PostStream::getWindowSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int
PostStream::window_size { getWindowSize() };

PostStream::PostStream(std::ostream &os):
    buf(window_size, os.rdbuf()),
    std::ostream(&buf)
{}

PostStream&
PostStream::indent(int w)
{
    this -> buf.set_indent(w);
    return *this;
}

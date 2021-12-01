#ifndef __TARGET_H__
#define __TARGET_H__

#include <string>
using namespace std;

enum
TargetType
{
    BOARD_LIST = 1,
    THREAD_LIST = 2,
    CATALOG = 3,
    THREAD = 4,
    MEDIA = 5
};

struct
Target
{
    TargetType type;
    unsigned int thread;
    string board, filename, ext;
};

#endif

#ifndef __CACHE_MANAGER_H__
#define __CACHE_MANAGER_H__

#include <ctime>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <unistd.h>
#include <sstream>
#include <sys/stat.h>
#include <iostream>

#define REFRESH_COOLDOWN 1
#define FILEEXISTS(_path_) (access(_path_.c_str(), F_OK) != -1)

#define PROGNAME "tbb"
#define API_URL "https://a.4cdn.org/"
#define MEDIA_URL "https://i.4cdn.org/"

using namespace std;

enum 
CacheManagerState
{
    NEVER_REFRESH = 0,
    FORCE_REFRESH = 1,
    REFRESH = 2
};

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

class
CacheManager
{
    private:
        CacheManagerState state;
        CURLcode curl_code;
        string cache_dir, config_file, cache_log;
        fstream log;
        time_t last_cache;
        bool cacheFile(const string&, const string&),
             createDir(const string&);
        inline bool dirExists(const string&);
        string getURL(const Target&);
    public:
            CacheManager();
            void setState(const CacheManagerState);
            string getPath(const Target&);
            bool prepCache(const Target&);
};

#endif

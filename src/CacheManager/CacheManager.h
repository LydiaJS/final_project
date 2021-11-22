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
#define API_URL "https://a.4cdn.org"

using namespace std;

enum CacheManagerState{
    NEVER_REFRESH = 0,
    REFRESH = 1,
    FORCE_REFRESH = 2
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
        bool cacheFile(const string&,const string&),
             createDir(const string&);
        inline bool dirExists(const string&);
        string getURL(const string&, const unsigned int);
    public:
            CacheManager();
            void setState(const CacheManagerState);
            bool prepCache(const string&, const unsigned int);
            string getContentPath(const string&,const unsigned int);
};

#endif

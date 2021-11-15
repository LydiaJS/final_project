#ifndef __CACHE_MANAGER_H__
#define __CACHE_MANAGER_H__

#include <ctime>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <unistd.h>
#include <sstream>
#include <sys/stat.h>

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
        string cache_path, config_file, cache_log;
        fstream log;
        const string API_url = "https://a.4cdn.org";
        time_t last_cache;
        bool cacheFile(const string&,const string&);
        bool createDir(const string&);
    public:
            CacheManager();
            bool prepCache(const string&, const unsigned int);
};

#endif

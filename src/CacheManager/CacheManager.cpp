#include "CacheManager.h"
#include <iostream>

CacheManager::CacheManager()
{
    this -> state = REFRESH;
    this -> cache_dir = string(getenv("HOME")) + "/." PROGNAME "/cache";
    if(!dirExists(this -> cache_dir))
        createDir(this -> cache_dir);
    this -> cache_log = this -> cache_dir + "/.cache.log";
    if(!FILEEXISTS(this -> cache_log))
    {
        this -> log.open( this -> cache_log, std::fstream::out);
        this -> log << 0; // retro
        this -> log.close();
        this -> last_cache = 0;
    } 
    else 
    {
        this -> log.open( this -> cache_log, std::fstream::in);
        this -> log >> this -> last_cache;
        this -> log.close();
    }
}

void
CacheManager::setState(const CacheManagerState in_state)
{
    this -> state = in_state;
}

string
CacheManager::getContentPath(const string& board, const unsigned int thread)
{
    string file_path;
    file_path = "/" + board;
    if(!thread)
        file_path += "/threads.json";
    else
        file_path += "/thread/" + std::to_string(thread) + ".json";
    return this -> cache_dir + file_path;
}

string
CacheManager::getURL(const string& board, const unsigned int thread)
{
    string file_path;
    file_path = "/" + board;
    if(!thread)
        file_path += "/threads.json";
    else
        file_path += "/thread/" + std::to_string(thread) + ".json";
    return API_URL + file_path;
}

bool
CacheManager::cacheFile(const string& url, const string &cache_dir)
{
    CURL *curl;
    FILE *cache;
    curl = curl_easy_init();
    if(curl)
    {
        cache = fopen(cache_dir.c_str(), "wb");
        if(!cache) 
            return false;

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, cache);
        
        this -> curl_code = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(cache);

        // Log the last time the program hit the API
        this -> last_cache = time(NULL);
        this -> log.open(this -> cache_log, std::fstream::out);
        this -> log << this -> last_cache;
        this -> log.close();
        return true;
    }
    return false;
}

bool
CacheManager::prepCache(const string& board,const unsigned int thread)
{
    string json_file, url;
    url = getURL(board, thread);
    json_file = getContentPath(board, thread);
    createDir(json_file.substr(0,json_file.find_last_of("/")));
    switch(this -> state)
    {
        case NEVER_REFRESH:
            return FILEEXISTS(json_file);
        case REFRESH:
            if(time(NULL) - this -> last_cache > REFRESH_COOLDOWN)
                break;
            if (FILEEXISTS(json_file))
                return true;
        case FORCE_REFRESH:
            while(time(NULL) - this -> last_cache <= REFRESH_COOLDOWN)
                sleep(1);
    }
    return cacheFile(url, json_file) || FILEEXISTS(json_file);
}

inline bool
CacheManager::dirExists(const string &path)
{
    struct stat st;
    return (!stat(path.c_str(), &st) && (st.st_mode & S_IFDIR));
}

bool
CacheManager::createDir(const string& path)
{
    stringstream path_stream;
    string segment, current_path;
    current_path = "";
    path_stream.str(path);
    while(std::getline(path_stream, segment, '/'))
    {
        if(!dirExists(current_path += "/" + segment))
            mkdir(current_path.c_str(),
                    S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    return dirExists(path);
}

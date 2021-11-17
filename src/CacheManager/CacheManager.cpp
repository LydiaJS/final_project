#include "CacheManager.h"
CacheManager::CacheManager()
{
    string home;
    home = getenv("HOME");
    this -> state = REFRESH;
    this -> cache_path = home + "/.final_project/cache";
    this -> cache_log = this -> cache_path + "/.cache.log";
    if(!dirExists(this -> cache_path))
        createDir(this -> cache_path);
    this -> log.open( this -> cache_log, std::fstream::in);
    if(this -> log.bad() || this -> log.eof())
        this -> last_cache = 0; // retro
    else
        this -> log >> this -> last_cache;
    this -> log.close();
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
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, cache);
        this -> curl_code = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(cache);
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
    /*
     * TODO: Fix this so it is more flexible/works with multiple APIs
     */

    string json_file, file_path;
    file_path = "/" + board;
    if(!thread)
        file_path += "/threads.json";
    else
        file_path += "/thread/" + std::to_string(thread) + ".json";
    json_file = this -> cache_path + file_path;
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
    return cacheFile(this->API_url + file_path, json_file) || 
        FILEEXISTS(json_file);
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
        current_path += "/" + segment;
        if(!dirExists(current_path))
            mkdir(current_path.c_str(),
                    S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    return dirExists(path);
}

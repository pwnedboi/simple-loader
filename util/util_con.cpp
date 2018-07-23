/*      con.cpp
 *
 *
 *
 */

#include "inc.h"
#include "util_con.h"

static string response;

/*
 *  writedata_post
 *  Writes the reponse to a string
 */
size_t writedata_post(void* ptr, size_t size, size_t nmemb, void* stream)
{
    unsigned long numbytes = size * nmemb;
    char lastchar = *((char*)ptr + numbytes - 1);
    
    *((char*)ptr + numbytes - 1) = '\0';
    response.append((char*) ptr);
    response.append(1, lastchar);
    *((char*)ptr + numbytes - 1) = lastchar;
    
    return size * nmemb;
}

/*
 *  post
 *  Sends a post request to a url and returns the response
 */
string post(string url, string data)
{
    // Clear the last response
    response = "";
    
    CURL* curl = curl_easy_init();;
    
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writedata_post);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    
    // Return new response
    return response;
}

/*
 *  download
 *  Downloads a file from a url to a given path, returns true if successfully downloaded
 */
bool download(string url, string out_path)
{
    FILE* fp;
    CURL* curl = curl_easy_init();
    
    if (curl)
    {
        fp = fopen(out_path.c_str(), "wb");
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [=](void* ptr, size_t size, size_t nmemb, FILE* stream) { return fwrite(ptr, size, nmemb, stream);});
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        fclose(fp);
    }
    
    return does_file_exist(out_path);
}


/*      loader.cpp
 *
 *
 *
 */

#include "inc.h"
#include "loader.h"
#include "util_con.h"
#include "injector.h"

const string download_url = "http://website.com/cheat.zip";

/*
 *  c_loader
 *  Constructor
 */
c_loader::c_loader(const string& cheat_name) : lib_name(cheat_name)
{
    
}

/*
 *  ~c_loader
 *  Destructor
 */
c_loader::~c_loader()
{
    
}

/*
 *  load
 *  Downloads the cheat and injects it
 */
void c_loader::load()
{
    check_for_csgo();
    
    // If the download folder doesnt exist then create it
    if(!does_file_exist(download_folder))
        mkdir(download_folder.c_str(), 0755);
    
    sleep(1);

    // The name of the zip
    const string zip = "cheat.zip";
    
    // The path where the zip will be downloaded
    const string out = download_folder + zip;
    
    // The command to unzip the cheat
    const string unzip = "cd " + download_folder + ";unzip " + zip;
    
    // Download the archived cheat from the server
    if(!download(download_url, out))
    {
        error("Unable to download the cheat from the server");
        quit(EXIT_FAILURE);
    }
    
    sleep(1);
    
    // Unzip the cheat
    system(unzip.c_str());
    
    sleep(1);
    
    c_injector injector(lib_name, download_folder);
    
    sleep(1);
    
    // Inject the cheat
    injector.inject();
    
    sleep(1);
}




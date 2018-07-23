/*      simple loader
 *
 *  A simple loader that is based off of my old loader
 *  without a few of the security features
 *
 *  Notes :
 *  - In logger.h change "loader" to whatever you want
 *  - Change download_folder to where ever you want to download the cheat
 *  - In main.cpp change "cheat.dylib" to the name of your dylib
 *  - Make sure that you have bootstrap and the cheat inside of the same zip
 *
 */

#include "inc.h"
#include "loader.h"

const string download_folder = "/Users/Shared/cheat/";

int main()
{
    // Clear the console
    system("clear");
    
    // If the file is not run as root then
    // quit and ask to be run as root
    if(geteuid() > 0)
    {
        print("Please run this as root");
        print("sudo ./" + string(__progname));
        quit(EXIT_FAILURE);
    }
    
    // Create a new loader, change this to the name of your dylib
    c_loader loader("cheat.dylib");
    
    // Load the cheat
    loader.load();
    
    // Clean up everything
    quit(EXIT_SUCCESS);
}

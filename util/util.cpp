/*      func.cpp
 *
 *
 *
 */

#include "inc.h"
#include "util.h"

/*
 *  does_file_exist
 *  Returns true if given file exists
 */
bool does_file_exist(const string& path)
{
    ifstream file(path);
    return   file.good();
}

/*
 *  quit
 *  Exits the program and cleans up
 */
void quit(int code)
{
    if(does_file_exist("/var/tmp/pwned-beta/"))
        system(string("sudo rm -R /var/tmp/pwned-beta/").c_str());
    
    exit(code);
}

/*
 *  get_process_by_name
 *  Returns the process id of a given process
 */
pid_t get_process_by_name(const char* name)
{
    int procCnt = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t pids[1024];
    memset(pids, 0, sizeof pids);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    
    for (int i = 0; i < procCnt; i++)
    {
        if (!pids[i])
            continue;
        
        char curPath[PROC_PIDPATHINFO_MAXSIZE];
        char curName[PROC_PIDPATHINFO_MAXSIZE];
        
        memset(curPath, 0, sizeof curPath);
        proc_pidpath(pids[i], curPath, sizeof curPath);
        size_t len = strlen(curPath);
        if(len)
        {
            size_t pos = len;
            while (pos && curPath[pos] != '/')
                --pos;
            
            strcpy(curName, curPath + pos + 1);
            if (!strcmp(curName, name))
                return pids[i];
            
        }
    }
    return 0;
}

/*
 *  check_for_csgo
 *  Checks if CS:GO is running
 */
void check_for_csgo()
{
    // If csgo is not running then quit
    if(!get_process_by_name("csgo_osx64"))
    {
        error("CS:GO is not running!");
        quit(EXIT_FAILURE);
    }
}

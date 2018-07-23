/*
 *
 *
 */

#include "inc.h"
#include "injector.h"

#include <dlfcn.h>
#include <mach/mach.h>
#include <mach/thread_act.h>
#include <mach/mach_init.h>

/*
 *  c_injector
 *  Constructor
 */
c_injector::c_injector(const string& path, const string& lib) : path(path), library_name(lib)
{
    string bootstrap_path = path + "bootstrap.dylib";
    module = dlopen(bootstrap_path.c_str(), RTLD_NOW | RTLD_LOCAL);
    
    if(!module)
    {
        error("Unable to locate bootstrap file");
        quit(EXIT_FAILURE);
    }
    
    bootstrapfn = dlsym(module, "bootstrap");
    
    if (!bootstrapfn)
    {
        error("Unable to locate bootstrap module");
        quit(EXIT_FAILURE);
    }
}

/*
 *  ~c_injector
 *  Destructor
 */
c_injector::~c_injector()
{
    if (module)
    {
        dlclose(module);
        module = NULL;
    }
}

/*
 *  inject
 *  Injects a library into a CS:GO
 */
void c_injector::inject()
{
    if (!module || !bootstrapfn)
    {
        error("Failed to inject");
        quit(EXIT_FAILURE);
    }
    
    // Get the path to the dylibs
    string lib_path = path + library_name;
    if(!does_file_exist(lib_path))
    {
        error("The given library doesnt exist");
        quit(EXIT_FAILURE);
    }
    
    // Get the csgo process
    pid_t csgo = get_process_by_name("csgo_osx64");
    if (!csgo)
    {
        error("CS:GO is not running");
        quit(EXIT_FAILURE);
    }
    
    // Inject
    mach_inject((mach_inject_entry)bootstrapfn, lib_path.c_str(), lib_path.length() + 1, csgo, 0);
    
    print("Injected!");
}

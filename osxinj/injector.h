#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include "mach_inject.h"

class c_injector
{
private:
    
    void* module;
    void* bootstrapfn;
    
    string path;
    string library_name;
    
public:
    
    c_injector(const string& path, const string& lib);
    ~c_injector();
    
    void inject();    
};

#endif

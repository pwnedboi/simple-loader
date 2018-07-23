/*
 *  inc.h
 *  Included everywhere
 */
#pragma once

#include <array>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <libproc.h>
#include <sys/stat.h>
#include <sys/proc_info.h>

#include <curl/curl.h>
#include <curl/easy.h>

using namespace std;
using namespace std::chrono;

#include "logger.h"

#include "util.h"

extern const char* __progname;
extern const string download_folder;

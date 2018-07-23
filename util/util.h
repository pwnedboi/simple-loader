/*
 *  util.h
 */
#pragma once

void    quit(int code);

void    check_for_csgo();
bool    does_file_exist(const string& path);
pid_t   get_process_by_name(const char* name);

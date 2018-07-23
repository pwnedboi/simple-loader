/*
 *  logger.h
 */
#pragma once

#include "console.h"

#define print(message)          log(message, LOG_DEFAULT,  "loader", fg::yellow)
#define debug(message, prefix)  log(message, LOG_DEFAULT,  prefix,   fg::yellow)
#define error(message)          log(message, LOG_ERROR)

enum LOG_LEVEL
{
    LOG_DEFAULT = 1,
    LOG_WARN    = 2,
    LOG_ERROR   = 3,
};

/*
 *  log
 *  A simple logger that prints to console
 */
template <class t>
void log(t message, int level = LOG_DEFAULT, std::string prefix = "log", fg color = fg::reset)
{
    switch (level)
    {
        case LOG_DEFAULT:
            std::cout << color      << "[" << prefix << "] " << style::reset << message << std::endl;
            break;
        case LOG_WARN:
            std::cout << fg::yellow << "[WARNING] " << style::reset << message << std::endl;
            break;
        case LOG_ERROR:
            std::cout << fg::red    << "[ERROR] "   << style::reset << message << std::endl;
            break;
        default:
            std::cout << color      << "[" << prefix << "] " << style::reset << message << std::endl;
            break;
    }
}

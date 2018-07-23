/*
 *  console.h | rang.hpp
 */
#pragma once

#include <atomic>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <algorithm>

enum class style
{
    reset   = 0,
    bold    = 1,
    dim     = 2,
    italic  = 3,
    underline= 4,
    blink   = 5,
    rblink  = 6,
    reversed= 7,
    conceal = 8,
    crossed = 9,
};

enum class fg
{
    reset   = 39,
    black   = 90,
    red     = 91,
    green   = 92,
    yellow  = 93,
    blue    = 94,
    magenta = 95,
    cyan    = 96,
    gray    = 97
};

enum class bg
{
    black   = 100,
    red     = 101,
    green   = 102,
    yellow  = 103,
    blue    = 104,
    magenta = 105,
    cyan    = 106,
    gray    = 107
};

/* dull colours
 
 enum class fg
 {
     black   = 30,
     red     = 31,
     green   = 32,
     yellow  = 33,
     blue    = 34,
     magenta = 35,
     cyan    = 36,
     gray    = 37,
     reset   = 39
 };
 
 enum class bg
 {
     black   = 40,
     red     = 41,
     green   = 42,
     yellow  = 43,
     blue    = 44,
     magenta = 45,
     cyan    = 46,
     gray    = 47,
     reset   = 49
 };
 
 */

enum class control
{                   // Behaviour of rang function calls
    Off     = 0,    // toggle off rang style/color calls
    Auto    = 1,    // (Default) autodect terminal and colorize if needed
    Force   = 2     // force ansi color output to non terminal streams
};

namespace rang
{
    
    inline std::atomic<control> &controlMode() noexcept
    {
        static std::atomic<control> value(control::Auto);
        return value;
    }
    
    inline bool supportsColor() noexcept
    {
        return []
        {
            const char *Terms[] =
            {
                "ansi",    "color",  "console", "cygwin", "gnome",
                "konsole", "kterm",  "linux",   "msys",   "putty",
                "rxvt",    "screen", "vt100",   "xterm"
            };
            
            const char* env_p = getenv("TERM");
            if(!env_p)
                return false;
            
            return std::any_of(std::begin(Terms), std::end(Terms), [&](const char *term) { return std::strstr(env_p, term) != nullptr; });
        }();
    }
    
    inline bool isTerminal(const std::streambuf *osbuf) noexcept
    {
        using std::cerr;
        using std::clog;
        using std::cout;
        if (osbuf == cout.rdbuf())
        {
            static const bool cout_term = isatty(fileno(stdout)) != 0;
            return cout_term;
        }
        else if (osbuf == cerr.rdbuf() || osbuf == clog.rdbuf())
        {
            static const bool cerr_term = isatty(fileno(stderr)) != 0;
            return cerr_term;
        }
        return false;
    }
    
    template <typename T>
    using enableStd = typename std::enable_if<
    std::is_same<T, style>::value || std::is_same<T, fg>::value ||
    std::is_same<T, bg>::value /* || std::is_same<T, fgB>::value|| std::is_same<T, bgB>::value */,
    std::ostream &>::type;
    
    template <typename T>
    inline enableStd<T> setColor(std::ostream &os, T const value)
    {
        return os << "\033[" << static_cast<int>(value) << "m";
    }
}

template <typename T>
inline rang::enableStd<T> operator<<(std::ostream &os, const T value)
{
    const control option = rang::controlMode();
    switch (option)
    {
        case control::Auto:
            return rang::supportsColor() && rang::isTerminal(os.rdbuf()) ? rang::setColor(os, value) : os;
        case control::Force:
            return rang::setColor(os, value);
        default:
            return os;
    }
}

inline void setControlMode(const control value) noexcept
{
    rang::controlMode() = value;
}


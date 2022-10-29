#ifndef CLOG_H
#define CLOG_H


#include <string.h>
#include <stdio.h>
#include <stdbool.h>


enum clog_verbosity {
    CLOG_SILENT,     // 0
    CLOG_FATAL,      // 1
    CLOG_ERROR,      // 2
    CLOG_WARNING,    // 3
    CLOG_INFO,       // 4
    CLOG_DEBUG,      // 5
};


extern enum clog_verbosity clog_verbosity;
extern const char * clog_verbosities [];


enum clog_verbosity clog_verbosity_from_string(char * verbosity);


void
clog_log(
        enum clog_verbosity level, 
        const char *filename,
        int lineno,
        const char *function,
        bool newline,
        const char *format, 
        ...);


#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


#define LOG(l, n, ...) \
    clog_log(l, __FILENAME__, __LINE__ , __FUNCTION__, n, __VA_ARGS__)


#define CR "\n"
#define DEBUG(...)   LOG(CLOG_DEBUG,   true, __VA_ARGS__)
#define INFO(...)    LOG(CLOG_INFO,    true, __VA_ARGS__)
#define WARN(...)    LOG(CLOG_WARNING, true, __VA_ARGS__)
#define ERROR(...)   LOG(CLOG_ERROR,   true, __VA_ARGS__)
#define FATAL(...)   LOG(CLOG_FATAL,   true, __VA_ARGS__)

#define DEBUGN(...)   LOG(CLOG_DEBUG,   false, __VA_ARGS__)
#define INFON(...)    LOG(CLOG_INFO,    false, __VA_ARGS__)
#define WARNN(...)    LOG(CLOG_WARNING, false, __VA_ARGS__)
#define ERRORN(...)   LOG(CLOG_ERROR,   false, __VA_ARGS__)
#define FATALN(...)   LOG(CLOG_FATAL,   false, __VA_ARGS__)

#define PRINTE(...)  dprintf(STDERR_FILENO, __VA_ARGS__)


#endif

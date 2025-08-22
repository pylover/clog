#ifndef CLOG_H
#define CLOG_H


/* standard */
#include <stdarg.h>
#include <unistd.h>


/* flags */
#define CLOG_NEWLINE 0x1
#define CLOG_HEADLESS 0x2
#define CLOG_NOERRNO 0x4


typedef char* (*clog_strerror_t) (int errnum);


enum clog_verbositylevel {
    CLOG_UNKNOWN = -1,
    CLOG_SILENT = 0,
    CLOG_FATAL = 1,
    CLOG_ERROR = 2,
    CLOG_WARN = 3,
    CLOG_INFO = 4,
    CLOG_DEBUG = 5,
    CLOG_TRACE = 6,
};


extern clog_strerror_t clog_strerror;
extern enum clog_verbositylevel clog_verbositylevel;
extern const char * clog_verbositylevels[];


enum clog_verbositylevel
clog_verbosity_from_string(const char * verbosity);


int
clog_vdprintf(int fd, int level, const char *file, unsigned int line,
        const char *func, int flags, const char *fmt, va_list fmtargs);


int
clog_dprintf(int fd, int level, const char *file, unsigned int line,
        const char *func, int flags, const char *fmt, ...);


#define CLOG(lev, flags, fmt, ...) if (clog_verbositylevel >= lev) \
    clog_dprintf( \
        lev <= CLOG_WARN? STDERR_FILENO: STDOUT_FILENO, \
        lev, \
        __FILE__, \
        __LINE__, \
        __func__, \
        flags, \
        fmt, \
        __VA_ARGS__)


// void
// clog_log(
//         enum clog_verbosity level,
//         const char *filename,
//         int lineno,
//         const char *function,
//         bool newline,
//         const char *format,
//         ...);
//
//
// void
// clog_vlog(
//         enum clog_verbosity level,
//         const char *filename,
//         int lineno,
//         const char *function,
//         bool newline,
//         const char *format,
//         va_list args);
//
//
// void
// clog_hless(enum clog_verbosity level, bool newline,
//         const char *format, ...);


// #define __BASEFILENAME__ \
//     (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
//
//
// #define LOG(l, n, ...) \
//     clog_log(l, __BASEFILENAME__, __LINE__ , __FUNCTION__, n, __VA_ARGS__)
//
//
// #define LOGV(l, n, ...) \
//     clog_vlog(l, __BASEFILENAME__, __LINE__ , __FUNCTION__, n, __VA_ARGS__)


// /* Variable arguments: format, ... */
// #define DEBUG2(...)  LOG(CLOG_DEBUG2,  true, __VA_ARGS__)
// #define DEBUG(...)   LOG(CLOG_DEBUG,   true, __VA_ARGS__)
// #define INFO(...)    LOG(CLOG_INFO,    true, __VA_ARGS__)
// #define WARN(...)    LOG(CLOG_WARNING, true, __VA_ARGS__)
// #define ERROR(...)   LOG(CLOG_ERROR,   true, __VA_ARGS__)
// #define FATAL(...)   LOG(CLOG_FATAL,   true, __VA_ARGS__)
//
// /* No newline appended */
// #define DEBUG2N(...)  LOG(CLOG_DEBUG2,  false, __VA_ARGS__)
// #define DEBUGN(...)   LOG(CLOG_DEBUG,   false, __VA_ARGS__)
// #define INFON(...)    LOG(CLOG_INFO,    false, __VA_ARGS__)
// #define WARNN(...)    LOG(CLOG_WARNING, false, __VA_ARGS__)
// #define ERRORN(...)   LOG(CLOG_ERROR,   false, __VA_ARGS__)
// #define FATALN(...)   LOG(CLOG_FATAL,   false, __VA_ARGS__)
//
// /* Headerless */
// #define DEBUG2H(...)  clog_hless(CLOG_DEBUG2,  true, __VA_ARGS__)
// #define DEBUGH(...)   clog_hless(CLOG_DEBUG,   true, __VA_ARGS__)
// #define INFOH(...)    clog_hless(CLOG_INFO,    true, __VA_ARGS__)
// #define WARNH(...)    clog_hless(CLOG_WARNING, true, __VA_ARGS__)
// #define ERRORH(...)   clog_hless(CLOG_ERROR,   true, __VA_ARGS__)
// #define FATALH(...)   clog_hless(CLOG_FATAL,   true, __VA_ARGS__)
//
// /* Headerless without trailing newline */
// #define DEBUG2NH(...)  clog_hless(CLOG_DEBUG2,  false, __VA_ARGS__)
// #define DEBUGNH(...)   clog_hless(CLOG_DEBUG,   false, __VA_ARGS__)
// #define INFONH(...)    clog_hless(CLOG_INFO,    false, __VA_ARGS__)
// #define WARNNH(...)    clog_hless(CLOG_WARNING, false, __VA_ARGS__)
// #define ERRORNH(...)   clog_hless(CLOG_ERROR,   false, __VA_ARGS__)
// #define FATALNH(...)   clog_hless(CLOG_FATAL,   false, __VA_ARGS__)
//
// /* va_list compatibility */
// #define DEBUG2V(...)  LOGV(CLOG_DEBUG2,  true, __VA_ARGS__)
// #define DEBUGV(...)   LOGV(CLOG_DEBUG,   true, __VA_ARGS__)
// #define INFOV(...)    LOGV(CLOG_INFO,    true, __VA_ARGS__)
// #define WARNV(...)    LOGV(CLOG_WARNING, true, __VA_ARGS__)
// #define ERRORV(...)   LOGV(CLOG_ERROR,   true, __VA_ARGS__)
// #define FATALV(...)   LOGV(CLOG_FATAL,   true, __VA_ARGS__)
//
// #define DEBUG2NV(...)  LOGV(CLOG_DEBUG2,  false, __VA_ARGS__)
// #define DEBUGNV(...)   LOGV(CLOG_DEBUG,   false, __VA_ARGS__)
// #define INFONV(...)    LOGV(CLOG_INFO,    false, __VA_ARGS__)
// #define WARNNV(...)    LOGV(CLOG_WARNING, false, __VA_ARGS__)
// #define ERRORNV(...)   LOGV(CLOG_ERROR,   false, __VA_ARGS__)
// #define FATALNV(...)   LOGV(CLOG_FATAL,   false, __VA_ARGS__)


#endif

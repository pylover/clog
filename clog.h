// Copyright 2025 Vahid Mardani
/*
 * This file is part of clog.
 *  clog is free software: you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation, either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  clog is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with clog. If not, see <https://www.gnu.org/licenses/>.
 *
 *  Author: Vahid Mardani <vahid.mardani@gmail.com>
 */
#ifndef CLOG_H_
#define CLOG_H_


/* standard */
#include <stdarg.h>
#include <unistd.h>


/* flags */
#define CLOGNNL 0x1
#define CLOGHLESS 0x2
#define CLOGNERRNO 0x4


#define CLOG(lev, flags, ...) if (clog_verbositylevel >= lev) \
    clog_dprintf( \
        lev <= CLOG_WARN? STDERR_FILENO: STDOUT_FILENO, \
        lev, \
        __FILE__, \
        __LINE__, \
        __func__, \
        flags, \
        __VA_ARGS__ )


#define CLOGV(lev, flags, fmt, valist) if (clog_verbositylevel >= lev) \
    clog_vdprintf( \
        lev <= CLOG_WARN? STDERR_FILENO: STDOUT_FILENO, \
        lev, \
        __FILE__, \
        __LINE__, \
        __func__, \
        flags, \
        fmt, \
        valist)


/* variable arguments: printf style, ... */
#define TRACE(...) CLOG(CLOG_TRACE, 0, __VA_ARGS__)
#define DEBUG(...) CLOG(CLOG_DEBUG, 0, __VA_ARGS__)
#define INFO(...) CLOG(CLOG_INFO, 0, __VA_ARGS__)
#define WARN(...) CLOG(CLOG_WARN, 0, __VA_ARGS__)
#define ERROR(...) CLOG(CLOG_ERROR, 0, __VA_ARGS__)
#define FATAL(...) CLOG(CLOG_FATAL, 0, __VA_ARGS__)


/* no trailing newline will be appended */
#define TRACEN(...) CLOG(CLOG_TRACE, CLOGNNL, __VA_ARGS__)
#define DEBUGN(...) CLOG(CLOG_DEBUG, CLOGNNL, __VA_ARGS__)
#define INFON(...) CLOG(CLOG_INFO, CLOGNNL, __VA_ARGS__)
#define WARNN(...) CLOG(CLOG_WARN, CLOGNNL, __VA_ARGS__)
#define ERRORN(...) CLOG(CLOG_ERROR, CLOGNNL, __VA_ARGS__)
#define FATALN(...) CLOG(CLOG_FATAL, CLOGNNL, __VA_ARGS__)


/* headless */
#define TRACEH(...) CLOG(CLOG_TRACE, CLOGHLESS, __VA_ARGS__)
#define DEBUGH(...) CLOG(CLOG_DEBUG, CLOGHLESS, __VA_ARGS__)
#define INFOH(...) CLOG(CLOG_INFO, CLOGHLESS, __VA_ARGS__)
#define WARNH(...) CLOG(CLOG_WARN, CLOGHLESS, __VA_ARGS__)
#define ERRORH(...) CLOG(CLOG_ERROR, CLOGHLESS, __VA_ARGS__)
#define FATALH(...) CLOG(CLOG_FATAL, CLOGHLESS, __VA_ARGS__)


/* user provided flags */
#define TRACEF(f, ...) CLOG(CLOG_TRACE, f, __VA_ARGS__)
#define DEBUGF(f, ...) CLOG(CLOG_DEBUG, f, __VA_ARGS__)
#define INFOF(f, ...) CLOG(CLOG_INFO, f, __VA_ARGS__)
#define WARNF(f, ...) CLOG(CLOG_WARN, f, __VA_ARGS__)
#define ERRORF(f, ...) CLOG(CLOG_ERROR, f, __VA_ARGS__)
#define FATALF(f, ...) CLOG(CLOG_FATAL, f, __VA_ARGS__)


/* va_list compatibility */
#define TRACEV(f, valist) CLOGV(CLOG_TRACE, 0, f, valist)
#define DEBUGV(f, valist) CLOGV(CLOG_DEBUG, 0, f, valist)
#define INFOV(f, valist) CLOGV(CLOG_INFO, 0, f, valist)
#define WARNV(f, valist) CLOGV(CLOG_WARN, 0, f, valist)
#define ERRORV(f, valist) CLOGV(CLOG_ERROR, 0, f, valist)
#define FATALV(f, valist) CLOGV(CLOG_FATAL, 0, f, valist)


/* types */
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


typedef void (*clog_exit_t) (int status);
typedef char* (*clog_strerror_t) (int errnum);

extern clog_exit_t clog_exit;
extern clog_strerror_t clog_strerror;
extern enum clog_verbositylevel clog_verbositylevel;
extern const char * clog_verbositylevels[];


enum clog_verbositylevel
clog_verbosity_from_string(const char * verbosity);


int
clog_vdprintf(int fd, enum clog_verbositylevel level, const char *file,
        unsigned int line, const char *func, int flags, const char *fmt,
        va_list fmtargs);


int
clog_dprintf(int fd, enum clog_verbositylevel level, const char *file,
        unsigned int line, const char *func, int flags, const char *fmt, ...);


#endif  // CLOG_H_

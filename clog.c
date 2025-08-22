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
/* standard */
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

/* thirdparty */
#include "clog.h"


// TODO: menuconfig
#define CONFIG_CLOG_HEADERMAX 512


char * clog_verbositylevels[] = {
    [CLOG_SILENT] = "silent",  // 0
    [CLOG_FATAL] = "fatal",  // 1
    [CLOG_ERROR] = "error",  // 2
    [CLOG_WARN] = "warn",  // 3
    [CLOG_INFO] = "info",  // 4
    [CLOG_DEBUG] = "debug",  // 5
    [CLOG_TRACE] = "trace",  // 6
};



clog_exit_t clog_exit = NULL;
clog_strerror_t clog_strerror = NULL;
enum clog_verbositylevel clog_verbositylevel = CLOG_DEBUG;


enum clog_verbositylevel
clog_verbosity_from_string(const char * verbosity) {
    if ((verbosity == NULL) || (strlen(verbosity) < 1)) {
        return CLOG_UNKNOWN;
    }

    switch (verbosity[0]) {
        case 's':
            return CLOG_SILENT;
        case 'f':
            return CLOG_FATAL;
        case 'e':
            return CLOG_ERROR;
        case 'w':
            return CLOG_WARN;
        case 'i':
            return CLOG_INFO;
        case 'd':
            return CLOG_DEBUG;
        case 't':
            return CLOG_TRACE;
        default:
            return CLOG_UNKNOWN;
    }
}


int
clog_vdprintf(int fd, enum clog_verbositylevel level, const char *file,
        unsigned int line, const char *func, int flags, const char *fmt,
        va_list fmtargs) {
    int len = 0;
    char header[CONFIG_CLOG_HEADERMAX];
    const char *fn;

    /* guards */
    if (fmt == NULL) {
        return -1;
    }

    if (!(flags & CLOGHLESS)) {
        if (clog_verbositylevel < CLOG_DEBUG) {
            /* print less information on header due the verbosity level */
            len = sprintf(header, "[%-5s] ", clog_verbositylevels[level]);
        }
        else {
            /* detailed information when verbosity level is >= debug */
            /* trim filename */
            fn = strrchr(file, '/');
            fn = fn ? fn + 1: file;
            len = sprintf(header, "[%-5s] [%s:%d %s] ",
                    clog_verbositylevels[level], fn, line, func);
        }
    }

    /* concat the user provided format into the end of the header */
    strcpy(header + len, fmt);
    len += strlen(fmt);

    /* errno and description */
    if ((!(flags & CLOGNERRNO)) && (level != CLOG_INFO) && errno) {
        len += sprintf(header + len, " -- %s. errno: %d",
                (clog_strerror? clog_strerror: strerror)(errno), errno);
    }

    /* trailing newline */
    if (!(flags & CLOGNNL)) {
        header[len++] = '\n';
    }
    header[len] = '\0';

    /* fire */
    len = vdprintf(fd, header, fmtargs);

    if (level == CLOG_FATAL) {
        (clog_exit? clog_exit: exit)(EXIT_FAILURE);
    }
    return len;
}


int
clog_dprintf(int fd, enum clog_verbositylevel level, const char *file,
        unsigned int line, const char *func, int flags, const char *fmt,
        ...) {
    va_list fmtargs;
    int len = 0;

    va_start(fmtargs, fmt);
    len = clog_vdprintf(fd, level, file, line, func, flags, fmt, fmtargs);
    va_end(fmtargs);
    return len;
}

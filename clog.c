/* standard */
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

/* thirdparty */
#include "clog.h"


// TODO: menuconfig
#define CONFIG_CLOG_HEADERMAX 512


clog_strerror_t clog_strerror = strerror;
enum clog_verbositylevel clog_verbositylevel = CLOG_DEBUG;


const char * clog_verbositylevels[] = {
    [CLOG_SILENT] = "silent",  // 0
    [CLOG_FATAL] = "fatal",  // 1
    [CLOG_ERROR] = "error",  // 2
    [CLOG_WARN] = "warn",   // 3
    [CLOG_INFO] = "info",   // 4
    [CLOG_DEBUG] = "debug",  // 5
    [CLOG_TRACE] = "trace",  // 6
};


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
clog_vdprintf(int fd, int level, const char *file, unsigned int line,
        const char *func, int flags, const char *fmt, va_list fmtargs) {
    int len = 0;
    char header[CONFIG_CLOG_HEADERMAX];
    const char *fn;

    /* guards */
    if (fmt == NULL) {
        return -1;
    }

    if (!(flags & CLOG_HEADLESS)) {
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
    if ((!(flags & CLOG_NOERRNO)) && (level != CLOG_INFO) && errno) {
        len += sprintf(header + len, " -- %s. errno: %d",
                clog_strerror(errno), errno);
    }

    /* trailing newline */
    if (flags & CLOG_NEWLINE) {
        header[len++] = '\n';
    }
    header[len] = '\0';

    /* fire */
    return vdprintf(fd, header, fmtargs);
}


int
clog_dprintf(int fd, int level, const char *file, unsigned int line,
        const char *func, int flags, const char *fmt, ...) {
    va_list fmtargs;
    int len = 0;

    va_start(fmtargs, fmt);
    len = clog_vdprintf(fd, level, file, line, func, flags, fmt, fmtargs);
    va_end(fmtargs);
    return len;
}


// void
// clog_log(int level, const char *file, int line, const char *func,
//         bool newline, const char *fmt, ...) {
//     va_list args;
//
//     if (fmt) {
//         va_start(args, fmt);
//     }
//
//     clog_vlog(level, file, line, func, newline, fmt, args);
//
//     if (fmt) {
//         va_end(args);
//     }
// }
//
//
// void
// clog_vlog(int level, const char *file, int line, const char *func,
//         bool newline, const char *fmt, va_list args) {
//     int fd = (level <= CLOG_ERROR)? STDERR_FILENO: STDOUT_FILENO;
//
//     if (level > clog_verbositylevel) {
//         return;
//     }
//
//     dprintf(fd, "[%-5s]", clog_verbosities[level]);
//     if (clog_verbositylevel >= CLOG_DEBUG) {
//         dprintf(fd, " [%s:%d %s]", file, line, func);
//     }
//
//     if (fmt) {
//         dprintf(fd, " ");
//         vdprintf(fd, fmt, args);
//     }
//
//     if (errno && (level != CLOG_INFO)) {
//         dprintf(fd, " -- %s. errno: %d", clog_strerror(errno), errno);
//     }
//
//     if (newline) {
//         dprintf(fd, CR);
//     }
//
//     if (level == CLOG_FATAL) {
//         exit(EXIT_FAILURE);
//     }
// }


// void
// clog_hless(enum clog_verbositylevel level, bool newline,
//         const char *fmt, ...) {
//     va_list args;
//     int fd = (level <= CLOG_ERROR)? STDERR_FILENO: STDOUT_FILENO;
//
//     if (level > clog_verbositylevel) {
//         return;
//     }
//
//     if (fmt) {
//         va_start(args, fmt);
//     }
//
//     vdprintf(fd, fmt, args);
//
//     if (newline) {
//         dprintf(fd, CR);
//     }
//
//     if (fmt) {
//         va_end(args);
//     }
//
//     if (level == CLOG_FATAL) {
//         exit(EXIT_FAILURE);
//     }
// }

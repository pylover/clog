#include "clog.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


enum clog_verbosity clog_verbosity = CLOG_DEBUG;


const char * clog_verbosities[] = {
    "never",   // 0
    "fatal",   // 1
    "error",   // 2
    "warn",    // 3
    "info",    // 4
    "debug",   // 5
};


void
clog_log(
        enum clog_verbosity level, 
        const char *filename,
        int lineno,
        const char *function,
        bool newline,
        const char *format, 
        ...) {
   
    va_list args;

    if (format) { 
        va_start(args, format);
    }

    clog_vlog(level, filename, lineno, function, newline, format, args);

    if (format) { 
        va_end(args);
    }
}


void
clog_hless(enum clog_verbosity level, bool newline, 
        const char *format, ...) {
    va_list args;
    int fd = (level <= CLOG_ERROR)? STDERR_FILENO: STDOUT_FILENO;

    if (level > clog_verbosity) {
        return;
    }

    if (format) { 
        va_start(args, format);
    }

    vdprintf(fd, format, args);

    if (newline) {
        dprintf(fd, CR);
    }

    if (format) { 
        va_end(args);
    }
    
    if (level == CLOG_FATAL) {
        exit(EXIT_FAILURE);
    }
}


void
clog_vlog(
        enum clog_verbosity level, 
        const char *filename,
        int lineno,
        const char *function,
        bool newline,
        const char *format, 
        va_list args) {
    int fd = (level <= CLOG_ERROR)? STDERR_FILENO: STDOUT_FILENO;

    if (level > clog_verbosity) {
        return;
    }
    
    dprintf(fd, "[%-5s]", clog_verbosities[level]);
    if (clog_verbosity == CLOG_DEBUG) {
        dprintf(fd, " [%s:%d %s]", filename, lineno, function);
    }
    
    if (format) { 
        dprintf(fd, " ");
        vdprintf(fd, format, args);
    }

    if (errno && (level != CLOG_INFO)) {
        dprintf(fd, " -- %s. errno: %d", strerror(errno), errno);
    }

    if (newline) {
        dprintf(fd, CR);
    }

    if (level == CLOG_FATAL) {
        exit(EXIT_FAILURE);
    }
} 


enum clog_verbosity 
clog_verbosity_from_string(char * verbosity) {
    switch (verbosity[0]) {
        case 's':
            return CLOG_SILENT;
        case 'f': 
            return CLOG_FATAL;
        case 'e': 
            return CLOG_ERROR;
        case 'w': 
            return CLOG_WARNING; 
        case 'i': 
            return CLOG_INFO;
        case 'd': 
        default:
            return CLOG_DEBUG;
    }
}

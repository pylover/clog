/* standard */
#include <stdio.h>
#include <errno.h>

/* thirdparty */
#include "clog.h"


void
fakeexit(int status) {
}


int
main() {
    int vl;

    /* suppress exit during fatal messages */
    clog_exit = fakeexit;

    printf("\n# NORMAL (HEADERFUL + errno)\n");
    errno = EINVAL;
    for (vl = 0; vl <= CLOG_TRACE; vl++) {
        clog_verbositylevel = vl;
        printf("\n## verbosity level: %s\n", clog_verbositylevels[vl]);
        TRACE("this is %s %s%s", "a", "Trace", " message");
        DEBUG("this is %s %s%s", "a", "Debug", " message");
        INFO("this is %s %s%s", "an", "Info", "");
        WARN("this is %s %s%s", "a", "Warning", "");
        ERROR("this is %s %s%s", "an", "Error", " message");
        FATAL("this is %s %s%s", "a", "Fatal", "");
    }

    printf("\n## no newline (CLOGNNL flag)\n");
    INFON("foo %s baz -- ", "bar");
    INFO("foo %s baz", "bar");
    ERRORN("foo %s baz -- ", "bar");
    ERROR("foo %s baz", "bar");

    printf("\n# no header (CLOGHLESS flag)\n");
    INFOH("this is %s %s%s", "an", "Info", "");
    WARNH("this is %s %s%s", "a", "Warning", "");
    ERRORH("this is %s %s%s", "an", "Error", " message");

    printf("\n# errno & strerr\n");
    WARN("foo %s baz", "bar");

    printf("\n## no errno processing (CLOGNERRNO flag)\n");
    WARNF(CLOGNERRNO, "foo %s baz", "bar");

    errno = 0;
    return 0;
}

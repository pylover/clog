/* standard */
#include <stdio.h>
#include <errno.h>

/* thirdparty */
#include "clog.h"


int
main() {
    int ll;
    int vl;

    printf("\n# NORMAL (HEADERFUL)\n");
    for (vl = 0; vl <= CLOG_TRACE; vl++) {
        clog_verbositylevel = vl;
        printf("\n## verbosity level: %s\n", clog_verbositylevels[vl]);
        for (ll = CLOG_FATAL; ll <= CLOG_TRACE; ll++) {
            CLOG(ll, CLOG_NEWLINE, "foo %s baz", "bar");
        }
    }

    printf("\n## no newline\n");
    CLOG(CLOG_INFO, 0, "foo %s baz -- ", "bar");
    CLOG(CLOG_INFO, 0, "foo %s baz\n", "bar");

    printf("\n# HEADLESS\n");
    CLOG(CLOG_INFO, CLOG_NEWLINE | CLOG_HEADLESS, "foo %s baz", "bar");

    printf("\n# ERROR strings(errno & strerr)\n");
    errno = EINVAL;
    CLOG(CLOG_WARN, CLOG_NEWLINE, "foo %s baz", "bar");
    errno = 0;

    printf("\n## CLOG_NOERRNO flag\n");
    errno = EINVAL;
    CLOG(CLOG_WARN, CLOG_NEWLINE | CLOG_NOERRNO, "foo %s baz", "bar");
    errno = 0;

    return 0;
}

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

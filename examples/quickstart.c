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
#include <errno.h>
#include <string.h>

#include "clog.h"


static const char *_customerror = "User defined error";


char *
_strerror(int errnum) {
    if (errnum < 0) {
        return (char *)_customerror;
    }

    return strerror(errnum);
}


int
main() {
    clog_verbositylevel = CLOG_DEBUG;
    clog_strerror = _strerror;

    errno = ECANCELED;
    ERROR("This is a system error");

    errno = -1;
    ERROR("This is a user defined error");
}

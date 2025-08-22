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

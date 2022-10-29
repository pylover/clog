#include "clog.h"

#include <stdlib.h>


void
test_clog_log() {
    INFO("Foo");
}


int main() {
    test_clog_log();
    return EXIT_SUCCESS;
}

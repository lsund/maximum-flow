
#include <stdlib.h>
#include "test.h"

char *utest_parse() {
    return NULL;
}

char *test_parser() {
    mu_message(UNIT, "parse\n");
    mu_run_utest(utest_parse);
    return NULL;
}

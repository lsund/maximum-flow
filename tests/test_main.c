
#include "test.h"

char *test_main()
{
    TokenTablePointer table = tokentable_init();
    tokenize("third_party/optima", table);
    size_t i;
    for (i = 1; i < table->populated_rows; i++) {
        char *file = tokentable_get(table, i, 0);
        char *s_opt = tokentable_get(table, i, 1);
        long opt = strtol(s_opt, NULL, 10);
        NetworkPointer network = network_init();
        parse(file, network);
        push_relabel(network);
        long res = (long) network_flow(network);
        mu_message(DATA, "testing file\n");
        printf("\t\%s with opt: %lu\n", file, opt);
        printf("\tfound: %lu\n", res);
        mu_assert("should give the same output as maxflow", res == opt);
        mu_message(DATA, "passed\n");
    }
    return NULL;
}


#include "test.h"


char *test_interop()
{
    TokenTablePointer table = tokentable_init();
    tokenize("third_party/optima", table);
    size_t i;
    for (i = 1; i < table->populated_rows; i++) {
        char *file = tokentable_get(table, i, 0);
        char *s_opt = tokentable_get(table, i, 1);
        long opt = strtol(s_opt, NULL, 10);
        NetworkPointer pr_network = network_init(PR);
        NetworkPointer ps_network = network_init(PS);
        parse(file, pr_network);
        push_relabel(pr_network);
        parse(file, ps_network);
        pseudoflow(ps_network);
        long pr_res = (long) network_flow(pr_network);
        long ps_res = (long) network_flow(ps_network);
        mu_message(DATA, "testing file\n");
        printf("\t\%s with opt: %lu\n", file, opt);
        printf("\tpr found: %lu\n", pr_res);
        printf("\tps found: %lu\n", ps_res);
        mu_assert("should comput the same flow", ps_res == ps_res);
        mu_message(DATA, "passed\n");
    }
    return NULL;
}

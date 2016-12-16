
#include "tokentable.h"

TokenTablePointer tokentable_init()
{
    TokenTablePointer ret = calloc(1, sizeof(TokenTable));
    char ***tokens;
    unsigned int i, j;
    tokens = calloc(MAX_LINES, sizeof(char **)); 
    for (i = 0; i < MAX_LINES; i++) {
        *(tokens + i) = calloc(LINE_MAX_TKNS, sizeof(char *));
        for (j = 0; j < LINE_MAX_TKNS; j++) {
            *(*(tokens + i) + j) = calloc(TKN_MAX_LEN, sizeof(char));
        }
    }
    ret->tokens = tokens;
    ret->rows = MAX_LINES;
    ret->populated_rows = 0;
    return ret;
}

char *tokentable_get(const TokenTablePointer table, const unsigned int row, const unsigned int col) 
{
    if (row >= table->populated_rows) { 
        return NULL;
    }
    return *(*(table->tokens + row) + col);
}

Point tokentable_graph_dimension(const TokenTablePointer table) 
{
    unsigned int i;
    Point ret; 
    for (i = 0; i < table->populated_rows; i++) {
        char *token = tokentable_get(table, i, 0);
        if (strcmp(token, "p") == 0) {
            ret.x = (unsigned int) strtol(tokentable_get(table, i, 2), NULL, 10);
            ret.y = (unsigned int) strtol(tokentable_get(table, i, 3), NULL, 10);
            return ret;
        }
    }
    ret.x = -1;
    ret.y = -1;
    return ret;
}

void tokentable_print(TokenTablePointer table)
{
    unsigned int i, j;
    printf("Table:\n");
    for (i = 0; i < table->populated_rows; i++) {
        for (j = 0; j < LINE_MAX_TKNS; j++) {
            printf("%s ", tokentable_get(table, i, j));             
        }
        printf("\n");
    }
}

void tokentable_destroy(TokenTablePointer table)
{
    if (!table) {
        runtime_error("tokentable_destroy: argument is null");
        return;
    }
    unsigned int i, j;
    for (i = 0; i < MAX_LINES; i++) {
        for (j = 0; j < LINE_MAX_TKNS; j++) {
            char *token =  *(*(table->tokens + i) + j);
            free(token);
            token = NULL;
        }
        char **tokenline = *(table->tokens + i);
        free(tokenline);
        tokenline = NULL;
    }
    free(table->tokens);
    free(table);
}
 

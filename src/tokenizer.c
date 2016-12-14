
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tokenizer.h"

static char tokenize_string(char *str, char **o_tokenized_string)
{
    unsigned int index;
    unsigned int len;
    index = 0; 
    char ret = str[0];
    while (str) {
        len = strlen(str);
        if (str && str[len - 1] == '\n') {
            str[len - 1] = 0; 
        } 
        sprintf(*(o_tokenized_string + index), "%s", str);
        index++;
        str = strtok(NULL, " ");
    }
    return ret;
}

static bool is_edge_row(const TokenTablePointer table, const unsigned int row) 
{
    if (strcmp(get_token(table, row, 0), "e") == 0) {
        return true;
    }
    return false;
}

Result make_tokentable(const char *fname, TokenTablePointer table)
{
    if (!fname || !table) {
        return FAIL;
    }
    if (table->initialized) {
        return FAIL;
    }
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        runtime_error("make_tokentable: could not open file");
	}

    int read;
    size_t file_len;
    unsigned int line_index;
    int edge_index;
    char *line, *str;
    line = NULL;
    str = NULL;
    file_len   = 0;
    line_index = 0;
    edge_index = 0;
    while ((read = getline(&line, &file_len, fp)) != -1) {
        str = strtok(line, " ");
        char **tokenrow = *(table->tokens + line_index);
        tokenize_string(str, tokenrow);
        if (is_edge_row(table, line_index)) {
            edge_index++;
        }
        line_index++;
    }
    if (line) {
        free(line);
    }
    table->populated_rows = line_index;
    if (graph_cardinality(table).y != edge_index) {
        runtime_error("make_tokentable: data malformed (number of edges unmatched)");
        fclose(fp);
        return FAIL;
    }
    table->initialized = 1;
    fclose(fp);
    return SUCCESS;
}

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

Point graph_cardinality(TokenTablePointer table) 
{
    unsigned int i;
    Point ret; 
    for (i = 0; i < table->populated_rows; i++) {
        char *token = get_token(table, i, 0);
        if (strcmp(token, "p") == 0) {
            ret.x = (unsigned int) strtol(get_token(table, i, 2), NULL, 10);
            ret.y = (unsigned int) strtol(get_token(table, i, 3), NULL, 10);
            return ret;
        }
    }
    errno = EINVAL;
    ret.x = -1;
    ret.y = -1;
    return ret;
}

char *get_token(const TokenTablePointer table, const unsigned int row, const unsigned int col) 
{
    return *(*(table->tokens + row) + col);
}

void print_tokentable(TokenTablePointer table)
{
    unsigned int i, j;
    printf("Table:\n");
    for (i = 0; i < table->populated_rows; i++) {
        for (j = 0; j < LINE_MAX_TKNS; j++) {
            printf("%s ", get_token(table, i, j));             
        }
        printf("\n");
    }
}

void destroy_tokentable(TokenTablePointer table)
{
    if (!table) {
        errno = EFAULT;
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
 

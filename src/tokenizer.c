
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
    bool is_a = strcmp(tokentable_get(table, row, 0), "a") == 0;
    bool is_e = strcmp(tokentable_get(table, row, 0), "e") == 0;
    return is_a || is_e;
}

Result tokenize(const char *fname, TokenTablePointer table)
{
    if (!fname || !table) {
        return FAIL;
    }
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        runtime_error("tokenize: could not open file");
	}

    int read;
    size_t file_len;
    unsigned int line_index;
    char *line, *str;
    line = str = NULL;
    file_len = line_index = 0;
    while ((read = getline(&line, &file_len, fp)) != -1) {
        str = strtok(line, " ");
        char **tokenrow = *(table->tokens + line_index);
        tokenize_string(str, tokenrow);
        table->populated_rows++;
        line_index++;
    }
    if (line) {
        free(line);
    }
    table->initialized = 1;
    fclose(fp);
    return SUCCESS;
}

TokenTablePointer tokenize_dimacs(const char *fname)
{
    TokenTablePointer table = tokentable_init();
    tokenize(fname, table);
    size_t i;
    int edge_index = 0;
    for (i = 0; i < table->populated_rows; i++) {
        if (is_edge_row(table, i)) {
            edge_index++;
        }
    }
    if (tokentable_graph_dimension(table).y != edge_index) {
        runtime_error("tokenize: data malformed (number of edges unmatched)");
        return NULL;
    }
    return table;
}


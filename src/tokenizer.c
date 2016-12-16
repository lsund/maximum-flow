
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
    if (strcmp(tokentable_get(table, row, 0), "e") == 0) {
        return true;
    }
    return false;
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
    int edge_index;
    char *line, *str;
    line = str = NULL;
    file_len = line_index = edge_index = 0;
    while ((read = getline(&line, &file_len, fp)) != -1) {
        str = strtok(line, " ");
        char **tokenrow = *(table->tokens + line_index);
        tokenize_string(str, tokenrow);
        table->populated_rows++;
        if (is_edge_row(table, line_index)) {
            edge_index++;
        }
        line_index++;
    }
    if (line) {
        free(line);
    }
    if (tokentable_graph_dimension(table).y != edge_index) {
        runtime_error("tokenize: data malformed (number of edges unmatched)");
        fclose(fp);
        return FAIL;
    }
    table->initialized = 1;
    fclose(fp);
    return SUCCESS;
}


#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "util.h"

// A tokentable is a matrix of tokens (strings)
// Field tokens:            The actual references to the tokens
// Field rows:              The vertical dimension of the matrix
// Field populated rows:    How many rows has content 
typedef struct tokentable {
    char ***tokens;
    unsigned int rows, populated_rows, initialized;
} TokenTable, *TokenTablePointer;

// Initialize a tokentable. All tokens get uninitialized values
TokenTablePointer init_tokentable();

// Construct a tokentable, populating it with the words in fname as tokens 
Result make_tokentable(const char *fname, TokenTablePointer table);

// The token stored at the specified row and column in the table
char *get_token(const TokenTablePointer table, const unsigned int row, const unsigned int col);

// The number of edges and vertices for the graph this table represents
Point graph_cardinality(const TokenTablePointer table);

// Prints the tokentable to stdout
void print_tokentable(const TokenTablePointer table);

// Free the structure
void destroy_tokentable(TokenTablePointer table);
#endif

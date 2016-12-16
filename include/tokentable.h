
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
TokenTablePointer tokentable_init();

// The token stored at the specified row and column in the table
char *tokentable_get(const TokenTablePointer table, const unsigned int row, const unsigned int col);

// The number of edges and vertices for the graph this table represents
Point tokentable_graph_dimension(const TokenTablePointer table);

// Prints the tokentable to stdout
void tokentable_print(const TokenTablePointer table);

// Free the structure
void tokentable_destroy(TokenTablePointer table);

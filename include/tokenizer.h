#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "tokentable.h"

// Construct a tokentable, populating it with the words in fname as tokens 
Result tokenize(const char *fname, TokenTablePointer table);

TokenTablePointer tokenize_dimacs(const char *fname);

#endif

#ifndef PARSER_H
#define PARSER_H

#include "network.h"
#include "tokenizer.h"

// Convert the tokens in the tokentable into graph structs, and load them into
// the specified graph 
Result parse(const char *filename, const NetworkPointer network);

#endif

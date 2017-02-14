#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "global.h"
#include "network.h"

// Convert the tokens in the tokentable into graph structs, and load them into
// the specified graph 
NetworkPointer parse(const char *filename, const NetworkType type);

#endif

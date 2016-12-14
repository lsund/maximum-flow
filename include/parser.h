#ifndef PARSER_H
#define PARSER_H

#include "network.h"
#include "tokenizer.h"

// Convert the tokens in the tokentable into graph structs, and load them into
// the specified graph 
Result parse(const TokenTablePointer table, const NetworkPointer network);

// Check validity of arguments given to program.
//  Return:
//      0 if arguments provided are invalid
//      1 if a graph but not a hint is provided correctly
//      2 if a graph and a hint are provided correctly
int parse_arguments(int argc, char *argv[]);

#endif

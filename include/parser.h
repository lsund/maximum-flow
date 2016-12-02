#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "tokenizer.h"
#include "graphstructs.h"
#include "util.h"

// Convert the tokens in the tokentable into graph structs, and load them into
// the specified graph 
Result parse(const TokenTablePointer table, const GraphPointer graph);

Result parse_edges(const TokenTablePointer table, 
                          EdgeSet edgeset, 
                          VertexPointer flat_edges,
                          VertexSet vertexset);

Result parse_vertices(const VertexSet vertexset);

#endif

#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "tokenizer.h"
#include "util.h"
#include "graphstructs.h"
#include "edgeset.h"
#include "vertexset.h"
#include "parser.h"

// Initializes a graph, it's components get default values
GraphPointer graph_init();

// Construct a graph, given a tokentable
Result graph_make(const TokenTablePointer table, GraphPointer graph);

// Frees the structure
Result graph_destroy(GraphPointer graph);

Result graph_make_reversed(const Graph graph, GraphPointer reversed);

#endif

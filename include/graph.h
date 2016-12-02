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

// Initializes a graph, it's components get uninitialized values
GraphPointer init_graph();

// Construct a graph, given a tokentable
Result make_graph(const TokenTablePointer table, GraphPointer graph);

// Frees the structure
Result destroy_graph(GraphPointer graph);

#endif

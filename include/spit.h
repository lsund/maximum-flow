#ifndef SPIT_H
#define SPIT_H

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "graph.h"

// Print a graph to stdout in DIMAC format
Result DIMACS_print(const GraphPointer graph);

#endif


#include "network_functions.h"
#include "pseudoflow_helpers.h"

typedef enum vertextype { SOURCE, SINK, NONE } VertexType; 

void pseudoflow_initialize(const NetworkPointer network);

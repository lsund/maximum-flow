
#include "network_functions.h"
#include "pseudoflow_network.h"

typedef enum vertextype { SOURCE, SINK, NONE } VertexType; 

void pseudoflow_initialize(const NetworkPointer network);

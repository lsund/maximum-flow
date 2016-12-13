#include "parser.h"

Result parse(const TokenTablePointer table, const NetworkPointer network)
{
    if (!table || !network) {
        return FAIL;
    }
    VertexSet vertexset = vertexset_init(graph_cardinality(table).x);
    EdgeSet edgeset = edgeset_init(graph_cardinality(table).y);
    size_t i;
    for (i = 0; i < network->graph->vertexset.set->capacity; i++) {
        VertexPointer vertex = vertex_p_make(i);
        vertexset_push(vertexset, vertex);
    }
    unsigned int row;
    int nedges;
    nedges = 0;
    for (row = 0; row < table->populated_rows; row++) {
        char *first_token, *second_token, *third_token;
        first_token = get_token(table, row, 0);
        if (strcmp("e", first_token) == 0) {
            second_token = get_token(table, row, 1);
            third_token  = get_token(table, row, 2);
            if (!second_token || !first_token) {
                errno = EFAULT;
                return FAIL;
            }
            Label label_first  = (int) strtol(second_token, NULL, 10) - 1;
            Label label_second = (int) strtol(third_token, NULL, 10) - 1;
            VertexPointer first_vertex = vertexset_get_with_label(vertexset, label_first);
            VertexPointer second_vertex = vertexset_get_with_label(vertexset, label_second);
            EdgePointer edge;
            if (first_vertex && second_vertex) {
                edge = edge_p_make_vertices(first_vertex, second_vertex);
            } else {
                edge = NULL;
                runtime_error("Parse edges: vertex null pointer");
            }
            edgeset_push(edgeset, edge);
            nedges++;
        }
    }
    GraphPointer graph = graph_make(vertexset, edgeset);
    network->graph = graph;
    return SUCCESS;
}

int parse_arguments(int argc, char *argv[]) {
    if ((argc == 3 || argc == 5) && strcmp(argv[1], "--network") == 0) {
        if (argc == 5 && strcmp(argv[3], "--hint") == 0) {
            return 2;
        } 
        return argc > 3 ? 0 : 1;
    } 
    return 0;
}


#include "parser.h"

Result parse_edges( const TokenTablePointer table, 
                    EdgeSet edgeset, 
                    VertexPointer flat_edges,
                    VertexSet vertexset)
{
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
            // TODO get with label
            VertexPointer first_vertex = vertexset_get(vertexset, label_first);
            VertexPointer second_vertex = vertexset_get(vertexset, label_second);
            EdgePointer edge;
            if (first_vertex && second_vertex) {
                edge = edge_p_make_vertices(first_vertex, second_vertex);
            } else {
                edge = NULL;
                runtime_error("Parse edges: vertex null pointer");
            }
            edgeset_push(edgeset, edge);
            if (flat_edges) {
                *(flat_edges + (2 * nedges))        = *edge->first;
                *(flat_edges + (2 * nedges + 1))    = *edge->second;
            }
            nedges++;
        }
    }
    return SUCCESS;
}

Result parse_vertices(const VertexSet vertexset) 
{
    size_t i;
    for (i = 0; i < vertexset.set->length; i++) {
        VertexPointer vertex = vertex_p_make(i);
        vertexset_push(vertexset, vertex);
    }
    return SUCCESS;
}

Result parse(const TokenTablePointer table, const GraphPointer graph)
{
    if (!table || !graph) {
        return FAIL;
    }
    VertexPointer flat_edges = calloc(graph->edgeset.set->capacity, sizeof(Vertex));
    if (!flat_edges) {
        errno = ENOMEM;
        free(flat_edges);
        return FAIL;
    }

    if (parse_vertices(graph->vertexset) == FAIL) {
        free(flat_edges);
        return FAIL;
    }
    
    if (parse_edges(table, graph->edgeset, flat_edges, graph->vertexset) == FAIL) {
        free(flat_edges);
        return FAIL;
    }


    free(flat_edges);
    return SUCCESS;
}

int parse_arguments(int argc, char *argv[]) {
    if ((argc == 3 || argc == 5) && strcmp(argv[1], "--graph") == 0) {
        if (argc == 5 && strcmp(argv[3], "--hint") == 0) {
            return 2;
        } 
        return argc > 3 ? 0 : 1;
    } 
    return 0;
}


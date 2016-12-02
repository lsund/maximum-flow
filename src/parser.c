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
            Edge e;
            second_token = get_token(table, row, 1);
            third_token  = get_token(table, row, 2);
            if (!second_token || !first_token) {
                errno = EFAULT;
                return FAIL;
            }
            e = make_edge(
                    *get_vertex(vertexset, (int) strtol(second_token, NULL, 10) - 1),
                    *get_vertex(vertexset, (int) strtol(third_token, NULL, 10) - 1)
                );
            EdgePointer edge = get_element(edgeset.set, nedges);
            if (!edge) {
                errno = EFAULT;
                return FAIL;
            }
            add_edge(edgeset, e);
            if (flat_edges) {
                *(flat_edges + (2 * nedges)) = e.first;
                *(flat_edges + (2 * nedges + 1)) = e.second;
            }
            nedges++;
        }
    }
    return SUCCESS;
}

Result parse_vertices(const VertexSet vertexset) 
{
    size_t i;
    for (i = 0; i < vertexset.maxvertices; i++) {
        Vertex vertex = make_vertex(i + 1);
        add_vertex(vertexset, vertex);
    }
    return SUCCESS;
}

Result parse(const TokenTablePointer table, const GraphPointer graph)
{
    if (!table || !graph) {
        return FAIL;
    }
    VertexPointer flat_edges = calloc(graph->edgeset.set->length, sizeof(Vertex));
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


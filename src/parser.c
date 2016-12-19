#include "parser.h"

static void parse_vertices(const VertexCollection vertexcollection, const unsigned int n_vertices)
{
    size_t i;
    for (i = 1; i <= n_vertices; i++) {
        VertexPointer vertex = vertex_p_make(i);
        vertexcollection_push(vertexcollection, vertex);
    }
}

static EdgePointer parse_edge(const VertexCollection vertexcollection, const char *first_token, const char*second_token)
{
    EdgePointer ret;
    Label label_first  = (unsigned int) strtol(first_token, NULL, 10);
    Label label_second = (unsigned int) strtol(second_token, NULL, 10);
    VertexPointer first_vertex = vertexcollection_get_with_label(vertexcollection, label_first);
    VertexPointer second_vertex = vertexcollection_get_with_label(vertexcollection, label_second);
    if (first_vertex && second_vertex) {
        ret = edge_p_make_vertices(first_vertex, second_vertex);
    } else {
        ret = NULL;
        runtime_error("Parse edges: vertex null pointer");
    }
    return ret;
}

static void update_source_sink(const NetworkPointer network, const char *first_token, const char *second_token)
{
    Label label  = (unsigned int) strtol(first_token, NULL, 10);
    if (strcmp(second_token, "s") == 0) {
        network->source = vertexcollection_get_with_label(network->graph.vertices, label);
    } else {
        network->sink = vertexcollection_get_with_label(network->graph.vertices, label);
    }
}

static EdgePointer update_edge(
        const VertexCollection vertexcollection, 
        const EdgeCollection edgecollection, 
        const char *first_token, 
        const char *second_token
    )
{
    EdgePointer edge = parse_edge(vertexcollection, first_token, second_token);
    edgecollection_push(edgecollection, edge);
    return edge;
}

static void update_capacity(
        const NetworkPointer network,
        const TokenTablePointer table,
        const EdgePointer edge,
        const unsigned int row
    )
{
    char *fourth_token = tokentable_get(table, row, 3);
    unsigned int capacity = (unsigned int) strtol(fourth_token, NULL, 10);
    networkedge_set_capacity(network, edge, capacity);
}

Result parse(const char *filename, const NetworkPointer network)
{
    if (!filename || !network) {
        return FAIL;
    }
    Point dimension;
    TokenTablePointer table = tokentable_init();
    tokenize_dimacs(filename, table);
    dimension = tokentable_graph_dimension(table);

    unsigned int n_vertices, n_edges;
    n_vertices = dimension.x;
    n_edges = dimension.y;

    parse_vertices(network->graph.vertices, n_vertices);

    network->capacities      = calloc(n_edges, sizeof(unsigned int));
    network->flows           = calloc(2 * n_edges, sizeof(int));
    network->distance_labels = calloc(n_vertices, sizeof(Label));

    unsigned int row;
    for (row = 0; row < table->populated_rows; row++) {
        char *first_token;
        first_token = tokentable_get(table, row, 0);

        bool is_n, is_e;
        is_n = strcmp("n", first_token) == 0;
        is_e = strcmp("a", first_token) == 0 || strcmp("e", first_token) == 0;

        if (is_n || is_e) {
            char *second_token, *third_token;
            second_token = tokentable_get(table, row, 1);
            third_token  = tokentable_get(table, row, 2);
            if (!second_token || !first_token) {
                return FAIL;
            }
            if (is_n) {
                update_source_sink(network, second_token, third_token);
            } else {
                EdgePointer edge = update_edge(
                        network->graph.vertices, 
                        network->graph.edges, 
                        second_token, 
                        third_token
                    );
                update_capacity(network, table, edge, row);
            }
        }
    }
    tokentable_destroy(table);

    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer p_edge = edgecollection_get(network->graph.edges, i);
        Edge reverse_edge = edge_swapped(*p_edge);
        edgecollection_push(network->reverse_edges, edge_p_make_edge(reverse_edge));
    }

    return SUCCESS;
}


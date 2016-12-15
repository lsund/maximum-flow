#include "parser.h"

static void parse_vertices(const VertexCollection vertexcollection, const unsigned int n_vertices)
{
    size_t i;
    for (i = 0; i < n_vertices; i++) {
        VertexPointer vertex = vertex_p_make(i);
        vertexcollection_push(vertexcollection, vertex);
    }
}

static EdgePointer parse_edge(const VertexCollection vertexcollection, const char *first_token, const char*second_token)
{
    EdgePointer ret;
    Label label_first  = (unsigned int) strtol(first_token, NULL, 10) - 1;
    Label label_second = (unsigned int) strtol(second_token, NULL, 10) - 1;
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
    Label label  = (unsigned int) strtol(first_token, NULL, 10) - 1;
    if (strcmp(second_token, "s") == 0) {
        network->source = vertex_p_make(label);
    } else {
        network->sink = vertex_p_make(label);
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
    char *fourth_token = get_token(table, row, 3);
    unsigned int capacity = (unsigned int) strtol(fourth_token, NULL, 10) - 1;
    network_set_edge_capacity(network, edge, capacity);
}

Result parse(const char *filename, const NetworkPointer network)
{
    if (!filename || !network) {
        return FAIL;
    }
    Point dimension;
    TokenTablePointer table = tokentable_init();
    make_tokentable(filename, table);
    dimension = graph_cardinality(table);

    unsigned int n_vertices, n_edges;
    n_vertices = dimension.x;
    n_edges = dimension.y;

    VertexCollection vertices;
    vertices = vertexcollection_init(n_vertices);
    parse_vertices(vertices, n_vertices);

    EdgeCollection edges;
    edges = edgecollection_init(n_edges);

    GraphPointer graph = graph_make(vertices, edges);
    network->graph = graph;

    network->capacities      = calloc(edgecollection_length(edges), sizeof(unsigned int));
    network->flows           = calloc(edgecollection_length(edges), sizeof(unsigned int));
    network->distance_labels = calloc(vertexcollection_length(vertices), sizeof(Label));

    unsigned int row;
    for (row = 0; row < table->populated_rows; row++) {
        char *first_token;
        first_token = get_token(table, row, 0);

        bool is_n, is_e;
        is_n = strcmp("n", first_token) == 0;
        is_e = strcmp("e", first_token) == 0;

        if (is_n || is_e) {
            char *second_token, *third_token;
            second_token = get_token(table, row, 1);
            third_token  = get_token(table, row, 2);
            if (!second_token || !first_token) {
                errno = EFAULT;
                return FAIL;
            }
            if (is_n) {
                update_source_sink(network, second_token, third_token);
            } else {
                EdgePointer edge = update_edge(vertices, edges, second_token, third_token);
                update_capacity(network, table, edge, row);
            }
        }
    }
    return SUCCESS;
}


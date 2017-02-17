#include "parser.h"

static void parse_vertices(
        const VertexCollection vertices, 
        const unsigned int n_vertices
    )
{
    size_t i;
    for (i = 1; i <= n_vertices; i++) {
        VertexPointer vertex = vertex_make(i);
        vertexcollection_push(vertices, vertex);
    }
}

static EdgePointer parse_edge(
        const VertexCollection vertices, 
        const char *first_token,
        const char *second_token
    )
{
    Label first_label, second_label;
    first_label = (unsigned int) strtol(first_token, NULL, 10);
    second_label = (unsigned int) strtol(second_token, NULL, 10);

    VertexPointer first_vertex, second_vertex;
    first_vertex = vertexcollection_get(vertices, first_label - 1);
    second_vertex = vertexcollection_get(vertices, second_label- 1);

    EdgePointer ret;
    if (first_vertex && second_vertex) {
        ret = edge_make(first_vertex, second_vertex);
    } else {
        ret = NULL;
        runtime_error("Parse edges: vertex null pointer");
    }
    return ret;
}

static void update_source_sink(
        const NetworkPointer network,
        const char *first_token,
        const char *second_token
    )
{
    VertexCollection vertices = network->graph.vertices;
    Label label  = (unsigned int) strtol(first_token, NULL, 10);
    if (strcmp(second_token, "s") == 0) {
        network->source = vertexcollection_get(vertices, label - 1);
    } else {
        network->sink = vertexcollection_get(vertices, label - 1);
    }
}

static EdgePointer update_edge(
        const NetworkPointer network,
        const char *first_token, 
        const char *second_token
    )
{
    EdgePointer edge = parse_edge(network->graph.vertices, first_token, second_token);
    edgecollection_push(network->graph.edges, edge);
    network_add_out_edge(network, edge->first, edge);
    network_add_out_edge(network, edge->second, edge->reverse);
    if (network->type == PS) {
        if (vertex_equals(edge->first, *network->source)) {
            VertexPointer vertex = edge->second_ref;
            vertexcollection_push(network->source_neighbours, vertex);
            edgecollection_push(network->source_edges, edge);
        } else if (vertex_equals(edge->second, *network->sink)) {
            VertexPointer vertex = edge->first_ref;
            vertexcollection_push(network->sink_neighbours, vertex);
            edgecollection_push(network->sink_edges, edge);
        }
    } else {
    }
    return edge;
}

static void update_capacity(
        const TokenTablePointer table,
        const EdgePointer edge,
        const unsigned int row
    )
{
    char *fourth_token = tokentable_get(table, row, 3);
    unsigned int capacity = (unsigned int) strtol(fourth_token, NULL, 10);
    edge_set_capacity(edge, capacity);
}

NetworkPointer parse(const char *filename, const NetworkType type)
{
    if (!filename) {
        return NULL;
    }
    Point dimension;
    TokenTablePointer table = tokenize_dimacs(filename);
    dimension = tokentable_graph_dimension(table);

    unsigned int n_vertices;
    n_vertices = dimension.x;

    NetworkPointer network = malloc(sizeof(Network));
    network_init(network, type, n_vertices);

    parse_vertices(network->graph.vertices, n_vertices);

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
                return NULL;
            }
            if (is_n) {
                update_source_sink(network, second_token, third_token);
            } else {
                EdgePointer edge = update_edge(
                        network,
                        second_token, 
                        third_token
                    );
                update_capacity(table, edge, row);
            }
        }
    }
    tokentable_destroy(table);

    return network;
}


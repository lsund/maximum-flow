#include "parser.h"

static void parse_vertices(
        const VertexCollection vertexcollection, 
        const unsigned int n_vertices
    )
{
    size_t i;
    for (i = 1; i <= n_vertices; i++) {
        VertexPointer vertex = vertex_p_make(i);
        vertexcollection_push(vertexcollection, vertex);
    }
}

static EdgePointer parse_edge(
        const VertexCollection vertexcollection, 
        const char *first_token, const char*second_token
    )
{
    EdgePointer ret;
    Label label_first  = (unsigned int) strtol(first_token, NULL, 10);
    Label label_second = (unsigned int) strtol(second_token, NULL, 10);
    VertexPointer first_vertex = vertexcollection_get_with_label(
            vertexcollection, 
            label_first
        );
    VertexPointer second_vertex = vertexcollection_get_with_label(
            vertexcollection, 
            label_second
        );
    if (first_vertex && second_vertex) {
        ret = edge_p_make_p_vertices(first_vertex, second_vertex);
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
        const NetworkPointer network,
        const char *first_token, 
        const char *second_token
    )
{
    EdgePointer edge = parse_edge(network->graph.vertices, first_token, second_token);
    edgecollection_push(network->graph.edges, edge);
    if (network->type == PS) {
        if (vertex_equals(edge->first, *network->source)) {
            VertexPointer vertex = vertexcollection_get_reference(network->graph.vertices, edge->second);
            vertexcollection_push(network->source_neighbours, vertex);
            edgecollection_push(network->source_edges, edge);
        } else if (vertex_equals(edge->second, *network->sink)) {
            VertexPointer vertex = vertexcollection_get_reference(network->graph.vertices, edge->first);
            vertexcollection_push(network->sink_neighbours, vertex);
            edgecollection_push(network->sink_edges, edge);
        }
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

static void add_reverse_edges(const NetworkPointer network) {
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        VertexPointer rev_first = edge->second_ref;
        VertexPointer rev_second = edge->first_ref;
        EdgePointer reverse_edge = edge_p_make_p_vertices(rev_first, rev_second);
        edgecollection_push(network->reverse_edges, reverse_edge);
        edge->reverse = reverse_edge;
        reverse_edge->reverse = edge;
        edge->is_reverse = false;
        reverse_edge->is_reverse = true;
        unsigned int key = edge_hash(*reverse_edge); 
        map_put(network->is_reverse, key, 1);
    }
}

NetworkPointer parse(const char *filename, const NetworkType type)
{
    if (!filename) {
        return NULL;
    }
    Point dimension;
    TokenTablePointer table = tokentable_init();
    tokenize_dimacs(filename, table);
    dimension = tokentable_graph_dimension(table);

    unsigned int n_vertices, n_edges;
    n_vertices = dimension.x;
    n_edges    = dimension.y;

    NetworkPointer network = malloc(sizeof(Network));
    network_init(network, type, n_vertices, n_edges);

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
                unsigned int key = edge_hash(*edge); 
                map_put(network->is_reverse, key, 0);
            }
        }
    }
    tokentable_destroy(table);
    add_reverse_edges(network);

    return network;
}



#Maximum Flow

A program for computing a maximum s-t-flow featuring implementations of two
different algorithms:

1. The Goldberg-Tarjan Algorithm (implemented accerding to Korte and Vygen,
   2002)
2. The Pseudoflow Algorithm (implemented according to Hochbaum xxxx)

The focus of the implementation has been comprehensibility.

Brief source code documentation can be found for all modules in `include/*.h`.

## Usage

the command `make` will generate the binary `./bin/main`

The usage is `./bin/main [filename]` where `filename` is an optional argument
holding the string containing the path to a DIMACS-formatted file containing a
graph.  Running the binary without the provided argument will run the algorithm
on a sample file using the pseudoflow algorithm. Have a look in `main.c` to
change these defaults.

A graph in the DIMACS format is assumed to have a known, specified number of
vertices and edges, a source vertex and a sink vertex.  Below is a description
of the DIMACS format. In this description, Items in angle brackets like `<item>`
are to be substituted by the appropriate value. The other symbols should remain
exactly as described. If the program notices a malformed line, it will halt with
an error messag.

* Lines that start with `c` are comments and are ignored by the file parser

* The first line which is not a comment should have the format 
`p max <n_vertices> <n_edges>`
where `n_vertices` and `n_edges` are substituted with the appropriate numbers
for the number of vertices and edges in the graph. The vertices are assumed to
be uniqely and increasingly numbered between 1 and `<n_vertices>`.  

* Following are two lines of format `n <source_id> s` and `n <sink_id> t` where
`source_id` and `sink_id` are the integers identifying the source and
the sink in the graph.

* The remaining lines describes the edges (arcs) and has the form `a A B U` where
`A` is the integer of the first vertex of this edge, `B` is the integer of the
second vertex of this edge and `U` is the capacity of this edge. Examples of
these files are stored in `sample_data`


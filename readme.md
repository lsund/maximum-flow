
#Maximum Flow

A program for computing a maximum s-t-flow featuring implementations of two
different algorithms:
1. The Goldberg-Tarjan Algorithm (implemented accerding to Korte and Vygen,
   2002)
2. The Pseudoflow Algorithm (implemented according to Hochbaum xxxx)
The focus of the implementation has been comprehensibility.

Brief source code documentation can be found for all modules in `include/*.h`.

## Usage

the command `make` will generate the binary `./bin/main`, run with `make run`.

otherwise, usage is `./bin/main [filename]`.
running the binary without the provided argument will run the algorithm on a
sample file using the pseudoflow algorithm. Have a look in `main.c` to change 
these defaults.

The argument should be the name of the file containing a graph described by the
DIMACS format. A graph in the DIMACS format is assumed to have `N` and `M` edges
and a source and a sink identified by integers `S` and `T`. `N` are assumed to
be numbered between 1 and `N` and `S` and `T` are integers in this range.
The following is a description of how the lines in a dimacs formatted file is
parsed:

Lines that start with `c` are comments and are ignored by the file parser

The first lines not a comment should have the format `p max N M`
where `N` and `M` are substituted with the appropriate numbers.

Following are two lines of format `n S s` and `n T t` where
`S` and `T` are the integers identifying the source and
the sink in the graph.

The remaining lines describes the edges (arcs) and has the form `a A B U` where
`A` is the integer of the first vertex of this edge, `B` is the integer of the
second vertex of this edge and `U` is the capacity of this edge. Examples of
these files are stored in `sample_data`


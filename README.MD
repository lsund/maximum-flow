
# Maximum Flow

A program for computing a maximum s-t-flow featuring implementations of two
different algorithms:

1. The Goldberg-Tarjan Algorithm [1]
2. The Pseudoflow Algorithm [2]

The project aims on demonstrating the properties of these algorithms and compare
them. The focus has thus been on clear and correctness of code rather than
execution speed.

## Usage

A brief description of all functions can be found in `include/*.h`.

the command `make` will generate the binary `./bin/main`

To run the program, use `./bin/main -f filename -t type` where `filename` is the
path to a DIMACS-formatted file containing a representation of a graph. `type`
is one of `pr`, `ps` or `both`. `pr` will run the Goldberg-Tarjan algorithm,
`ps` will run the pseudoflow algorithm and `both` will run both (!).

### Input

A graph in the DIMACS format is assumed to have a known, specified number of
vertices and edges, a source vertex and a sink vertex.  Below is a description
of the DIMACS format. In this description, Items in angle brackets like `<item>`
are to be substituted by the appropriate value. The other symbols should remain
exactly as described. If the program notices a malformed line, it will halt with
an error message.

* Lines that start with `c` are treated as comments and are ignored by the
  parser

* The first line which is not a comment should have the format 

  `p max <n_vertices> <n_edges>` 

  where `n_vertices` and `n_edges` are substituted with the appropriate numbers
  for the number of vertices and edges in the graph. The vertices are assumed to
  be uniqely and increasingly numbered between 1 and `<n_vertices>`.  

* Following are two lines of format 

`n <source_id> s` and `n <sink_id> t` where

 `source_id` and `sink_id` are the integers identifying the source and the sink
  in the graph.

* The remaining lines describes the edges (arcs) and has the form 

  `a <first_id> <second_id> <capacity>` 

  where `first_id` is the integer of the first vertex of this edge, `second_id`
  is the integer of the second vertex of this edge and `capacity` is the
  capacity of this edge. Examples of these files are stored in `sample_data`

### Output

If everything goes well, then the program writes two or three space separated
numbers to standard output.  The first is the number of vertices of the graph
that was specified.  If `type` is `pr` or `ps` then the second number is the
time that the corresponding algorithm took to calculate the maximum flow of the
specified graph. If `type` is `both` then the second number is the time that the
Goldberg-Tarjan algorithm took, and the third number is the time the Pseudoflow
algorithm took to compute the maximum flow in the specified graph. Time is given
in milliseconds.

## Improvements

* Efficiency of algorithm 2 could probably be improved by at least a factor 2 by
  improving the merger-edge search. The approach is described in [2].

* Flow recovery of algorithm 2 is rather complicated and currently implemented a
  bit hackish. Could be improved for efficiency and comprehensibility.

## References

[1] Combinatorial Optimization Theory and Algorithms Second Edition, 
Bernhard Korte, Jens Vygen, 2002, p 163-168.

[2] The Pseudoflow Algorithm: A new Algorithm for the Maximum-Flow Problem, 
Dorit S. Hochbaum, 2001.


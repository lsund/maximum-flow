# Objective

compare:

The Goldberg Tarjan Algorithm (GT)

The Pseudoflow algorithm (PSEUDO)

# What was implemented / Programming language

GT implemented according to Korte, Vygen 2002

PSEUDO implemented according to Hochbaum 2001 (paper)
"The generic algorithm"

Program runs both algorithms, outputs the time taken

# Difficulties

## GT

* Idea was to implement own version of push-relabel, then specialize. Turned out
  to be a Mistake.

* When implementing directly to the specification of GT, it worked almost
  'magically'.

## PSEUDO

* Main difficulty: Understand how the algorithm works

* In constrast to more traditional algorithms like GT, it solves the max.
  blocking cut problem: find a subset of nodes that maximizes the sum of node
  weights, minus the capacities of the arcs leaving the subset.

* Maintains a tree structure. First intention was to use a tree datastructure
  from a different project, but turned out to be a mistake. All you need is 
  parent pointers at the nodes.

* Once you have all the data structures, you write a code 'skeleton', that may
  not work but you know what you _want_ it to do.

* The last step is really understanding all details of the algorithm. When you
  undertand everything, you can start fixing the bugs.
  The main difficulty for me was understanding how residual paths corresponded
  between the graph and the tree.

# Programming Language: plain C

* minimal: gives you (too ?) many choices. Easiest to implement things from
  scratch.

* Memory management: Increases overhead, Valgrind

# Theoretical Running time

# GT O(n^3)

Discharge procedure relabel only calls when v is active and no outging edge is
admissable. This leads into the fact that the maximum number of pushes is
O(4n^3)

# Pseudoflow O(mn logn)

* Merger iterations: O(mn)
* Splits: O(mn)

Each iteration:

1. Identifying merger arc                               O(m) (total: O(mn))
2. Inverting and merging edges                          O(logn)
3. Updating residual capacities along the path          O(logn)
4. finding the next split edge along the merger path    O(logn)

Total: O(nm log(n))

# Comparison of running times

* Instance sizes: 9 - 10 000 nodes
* about 5 instances per size (times averagized and plotted)
* Instances dense (O(n^2) edges)
* algorithms pretty similar in average. We notice that PSEUDO is a lot more
  'even' than GT, which differs alot in runnig time

Both algorithm are correct for all instances tested on. About 2000 randomly
generated graphs.

# Conclusion

PSEUDO gives you a speedup in runtime, especially if graph is sparse and you
implement it with perfect data structures according to your needs.
Tradeoff is program complexity.

PSEUDO needs a little extra space for additional structures, but nothing
critical.

In Hochbaums own paper, she considers GT efficient in in many cases
better in practice. Her best pseudoflow implementation is in general a factor 2
better than GT on standard benchmark instances.

We did not implement merger arc scanning and flow recovery in the optimal way.
It is then hard to beat GT

Implementation: Main lesson that it is important to completely understand which
datastructures you need before trying to implement an algorithm. Understand if
the specification of the algorithm is precise and well thought out, or just a
more hight level method. In this case it would have been better follow the
specification more directly from the start.



# Ford Fulkerson Algorithm

The Ford–Fulkerson method or Ford–Fulkerson algorithm (FFA) is an algorithm that computes the maximum flow in a flow network.

The runtime is O(|E|f) where |E| is the number of edges and f is the maximum flow in the graph. This is because each augmenting path can be found in O(|E|) time (with partial BFS) and increases the flow by at least 1.

graph.txt is from https://www.youtube.com/watch?v=-8MwfgB-lyM

The format of graph.txt is for each line, the first number is the vertex, followed by neighbor and edge weight.

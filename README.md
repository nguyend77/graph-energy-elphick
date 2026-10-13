# GOAL

Let $G$ be a graph with $n$ vertices and $m$ edges.

We define a graph energy $\mathcal{E}$ as the sum of absolute values of eigenvalues of the graph adjacency matrix:

$$ \mathcal{E} = \sum_{i=1}^{n} |\lambda_i|. $$

It is conjectured that for all simple, connected, undirected graphs,

$$ \mathcal{E} \le \frac{2m}{\sqrt{\lambda_1}}, $$

where $\lambda_1$ is the spectral radius, the largest eigenvalue of the adjacency matrix.

We represent a graph with $n$ vertices as an $\frac{n(n-1)}{2}$ chars string by flattening out the lower triangular entries of the adjacency matrix. In otherwords, given a string $S$ presenting a graph and pair of vertices $i>j$, let

$$ k = \frac{i(i-1)}{2} + j. $$

There is an edge between $i,j$ if `S[k] = '1'`.

Since the graph is simple, the diagonal entries are all 0s. Since the graph is undirected, the adjacency matrix is symmetric over the diagonal.

We shall conduct a brute force counterexample search for on all graphs with $n$ vertices for $n = 2, 3, 4, \dots , 10$.

# SETUP
We use the `geng` tool from the `nauty` software package to generate all non-isomorphic graphs of size $n$. If the `cpp/data/input/` folder is empty, run the following command from the project root.

```sh
for n in {2..10}; do nauty-geng -cq $n > "cpp/data/input/${n}vertices.txt"; done
```

Compile the main executable using the provided [Makefile](cpp/Makefile).

```sh
cd cpp
make
```

Run the executable. The results will be placed under `cpp/data/output/`.

```sh
cd cpp
bin/main
```

import matplotlib.pyplot as plt
import networkx as nx
from pathlib import Path

ROOT = Path(__file__).parent.parent.parent
READ = ROOT/"data/output"

def draw(graph: str, vertices: int, name: str) -> None:
    G = nx.Graph()
    G.add_nodes_from(range(vertices))
    for i in range(1, vertices):
        for j in range(i):
            if graph[i*(i-1)//2 + j] == '1':
                G.add_edge(i, j)
    fig = plt.figure()
    nx.draw(G, pos=nx.kamada_kawai_layout(G))
    fig.savefig(f"../../figures/{name}.png")
    plt.close(fig)

def report(start: int, end: int) -> None:
    with open(ROOT/"counterexamples.md", "a") as out_file:
        for v in range (start, end):
            out_file.write(f"## {v} vertices\n\n")
            i = 1
            with open(f"{READ}/{v}vertices.txt") as in_file:
                lines = in_file.readlines()
            for j in range(len(lines)):
                line = lines[j] 
                if (
                    line[0] == '\n'
                    or line[0] == '-'
                    or line[0] == 'R'
                    or line[0] == 'T'
                ):
                    pass
                elif (line[1] != ' '):
                    graph = line.rstrip('\n')
                    name = f"{v}_{i}"
                    draw(graph, v, name)
                    out_file.write(f"![{name}](figures/{name}.png)\n\n")
                    i += 1

if __name__ == "__main__":
    report(9,12)

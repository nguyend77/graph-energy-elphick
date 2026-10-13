import matplotlib.pyplot as plt
import networkx as nx

def draw(graph: str, vertices: int, name: str) -> None:
    G = nx.Graph()
    G.add_nodes_from(range(vertices))
    for i in range(1, vertices):
        for j in range(i):
            if graph[i*(i-1)//2 + j] == '1':
                G.add_edge(i, j)
    fig = plt.figure()
    nx.draw(G, pos=nx.spring_layout(G))
    fig.savefig(f"figures/{name}.png")
    plt.close(fig)

if __name__ == "__main__":
    draw("000000100001000001000000100011111000", 9, "9a")
    draw("000000100001000001000000100011111100", 9, "9b")
    draw("000000000010000010000001000000010000111110000", 10, "10a")
    draw("000000100001000001000000100010001000111110001", 10, "10b")
    draw("000000100001000001000100100011001000101010001", 10, "10c")

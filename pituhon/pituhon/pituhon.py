class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = []
        self.nodes = []

    def add_edge(self, s, d, w):
        self.graph.append([s, d, w])

    def add_node(self, value):
        self.nodes.append(value)

    def bellman_ford(self, source):
        distances = {i: float("Inf") for i in self.nodes}
        distances[source] = 0

        for _ in range(self.vertices - 1):
            for s, d, w in self.graph:
                if distances[s] != float("Inf") and distances[s] + w < distances[d]:
                    distances[d] = distances[s] + w

        for s, d, w in self.graph:
            if distances[s] != float("Inf") and distances[s] + w < distances[d]:
                print("Graph contains negative cycle")
                return

        print(distances)


def main():
    g = Graph(5)
    g.add_node("0")
    g.add_node("1")
    g.add_node("2")
    g.add_node("3")
    g.add_node("4")
    g.add_node("5")
    g.add_edge("0", "1", -2)
    g.add_edge("0", "2", 7)
    g.add_edge("0", "3", 4)
    g.add_edge("0", "4", 6)
    g.add_edge("0", "5", 3)
    g.add_edge("1", "0", 3)
    g.add_edge("1", "2", 4)
    g.add_edge("1", "3", 5)
    g.add_edge("1", "4", -6)
    g.add_edge("1", "5", 1)
    g.add_edge("2", "0", -2)
    g.add_edge("2", "1", 4)
    g.add_edge("2", "3", -8)
    g.add_edge("2", "4", 7)
    g.add_edge("3", "0", -4)
    g.add_edge("3", "2", 8)
    g.add_edge("3", "4", 5)
    g.add_edge("3", "5", 7)
    g.add_edge("4", "1", 7)
    g.add_edge("4", "2", 8)
    g.add_edge("4", "3", 4)
    g.add_edge("4", "5", 3)
    g.add_edge("5", "0", 2)
    g.add_edge("5", "1", 4)
    g.add_edge("5", "3", -7)
    g.add_edge("5", "4", -8)
    g.bellman_ford("2")




if __name__ == "__main__":
    main()

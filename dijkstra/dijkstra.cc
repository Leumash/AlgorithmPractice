#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
    public:
        void addVertex(int v) {
            adjacencyList[v];
        };
        void addEdge(int u, int v, int weight) {
            addVertex(u);
            addVertex(v);
            adjacencyList[u].push_back(make_pair(v, weight));
        };
        vector<pair<int,int>> getNeighbors(int v) {
            if (adjacencyList.find(v) != adjacencyList.end()) {
                return vector<pair<int,int>>(adjacencyList[v].begin(), adjacencyList[v].end());
            }
            return vector<pair<int,int>>();
        };
    private:
        unordered_map<int, vector<pair<int,int>>> adjacencyList;
};

Graph makeGraph() {
    Graph graph;
    graph.addEdge(1, 2, 7);
    graph.addEdge(1, 3, 9);
    graph.addEdge(1, 6, 14);
    graph.addEdge(2, 1, 7);
    graph.addEdge(2, 3, 10);
    graph.addEdge(2, 4, 15);
    graph.addEdge(3, 1, 9);
    graph.addEdge(3, 2, 10);
    graph.addEdge(3, 4, 11);
    graph.addEdge(3, 6, 2);
    graph.addEdge(4, 2, 15);
    graph.addEdge(4, 3, 11);
    graph.addEdge(4, 5, 6);
    graph.addEdge(5, 4, 6);
    graph.addEdge(5, 6, 9);
    graph.addEdge(6, 1, 14);
    graph.addEdge(6, 3, 2);
    graph.addEdge(6, 5, 9);
    return graph;
}

int main() {
    Graph graph = makeGraph();
    /*
    for (int vertex : getShortedPath(graph, 1, 5)) {
        cout << vertex << ' ';
    }
    */
    cout << endl;
}


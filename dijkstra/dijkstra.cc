#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

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
        vector<int> getVertices() {
            vector<int> vertices;
            for (auto kv : adjacencyList) {
                vertices.push_back(kv.first);
            }
            return vertices;
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

int findCheapest(unordered_map<int,int> &vertexToCost) {
    int vertex;
    int cost = INT_MAX;
    for (auto vToC : vertexToCost) {
        if (vToC.second < cost) {
            cost = vToC.second;
            vertex = vToC.first;
        }
    }
    return vertex;
}

void dijkstrasAlgorithm(Graph &graph, int s, unordered_map<int,int> &parents) {
    unordered_map<int,int> cheapestCost;
    unordered_map<int,int> currentCost;
    vector<int> vertices = graph.getVertices();
    unordered_set<int> visited;
    for (int vertex : vertices) {
        currentCost[vertex] = INT_MAX;
    }
    currentCost[s] = 0;
    // Visit every vertex
    while (visited.size() < vertices.size()) {
        int current = findCheapest(currentCost);
        cheapestCost[current] = currentCost[current];
        currentCost.erase(current);
        visited.insert(current);
        for (pair<int,int> neighborAndWeight : graph.getNeighbors(current)) {
            if (visited.find(neighborAndWeight.first) == visited.end()) {
                if (currentCost[neighborAndWeight.first] > cheapestCost[current] + neighborAndWeight.second) {
                    currentCost[neighborAndWeight.first] = cheapestCost[current] + neighborAndWeight.second;
                    parents[neighborAndWeight.first] = current;
                }
            }
        }
    }
}

vector<int> getShortedPath(Graph &graph, int s, int t) {
    unordered_map<int,int> parents;
    dijkstrasAlgorithm(graph, s, parents);
    vector<int> shortestPath;
    shortestPath.push_back(t);
    int i = t;
    while (i != s) {
        i = parents[i];
        shortestPath.push_back(i);
    }
    reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}

int main() {
    Graph graph = makeGraph();
    for (int vertex : getShortedPath(graph, 1, 5)) {
        cout << vertex << ' ';
    }
    cout << endl;
}


/*
The Ford–Fulkerson method or Ford–Fulkerson algorithm (FFA) is an algorithm that computes the maximum flow in a flow network.
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Edge
{
    int vertex;
    int weight;
    Edge(int v, int w) : vertex(v), weight(w) {}
};

class Graph
{
    public:
        void AddVertex(int vertex);
        void AddEdge(int u, int v, int weight);
        void UpdateEdge(int u, int v, int toAdd);
        int GetEdgeWeight(int u, int v) const;
        vector<int> GetVertices() const;
        vector<Edge> GetEdges(int vertex) const;
    private:
        unordered_map<int,vector<Edge>> adjacencyList;
};

void Graph::AddVertex(int vertex)
{
    if (adjacencyList.count(vertex) == 0)
    {
        adjacencyList[vertex] = vector<Edge>();
    }
}

void Graph::AddEdge(int u, int v, int weight)
{
    AddVertex(u);
    AddVertex(v);

    adjacencyList[u].push_back(Edge(v, weight));
}

void Graph::UpdateEdge(int u, int v, int toAdd)
{
    for (Edge &edge : adjacencyList[u])
    {
        if (edge.vertex == v)
        {
            edge.weight += toAdd;
            break;
        }
    }
}

int Graph::GetEdgeWeight(int u, int v) const
{
    if (adjacencyList.count(u) > 0)
    {
        for (const Edge &edge : adjacencyList.at(u))
        {
            if (edge.vertex == v)
            {
                return edge.weight;
            }
        }
    }

    return 0;
}

vector<int> Graph::GetVertices() const
{
    vector<int> vertices;

    for (const auto &vertexToNeighbors : adjacencyList)
    {
        vertices.push_back(vertexToNeighbors.first);
    }

    return vertices;
}

vector<Edge> Graph::GetEdges(int vertex) const
{
    if (adjacencyList.count(vertex) > 0)
    {
        return adjacencyList.at(vertex);
    }

    return vector<Edge>();
}

Graph ReadGraph()
{
    int vertex;
    int neighbor;
    int weight;
    string line;
    Graph graph;

    while (cin >> vertex)
    {
        graph.AddVertex(vertex);

        getline(cin, line);

        stringstream ss;

        ss << line;

        while (ss >> neighbor >> weight)
        {
            graph.AddEdge(vertex, neighbor, weight);
        }
    }

    return graph;
}

int GetSource(const Graph &graph)
{
    vector<int> vertices = graph.GetVertices();

    return *min_element(vertices.begin(), vertices.end());
}

int GetSink(const Graph &graph)
{
    vector<int> vertices = graph.GetVertices();

    return *max_element(vertices.begin(), vertices.end());
}

bool BFS(const Graph &graph, int s, int t, unordered_map<int,int> &parent)
{
    parent.clear();
    unordered_set<int> visited;
    queue<int> toTraverse;
    visited.insert(s);
    toTraverse.push(s);

    while (!toTraverse.empty())
    {
        int currentVertex = toTraverse.front();
        toTraverse.pop();

        for (const Edge &edge : graph.GetEdges(currentVertex))
        {
            if ((visited.count(edge.vertex) == 0) && edge.weight > 0)
            {
                toTraverse.push(edge.vertex);
                parent[edge.vertex] = currentVertex;
                visited.insert(edge.vertex);
            }
        }
    }

    return visited.count(t) > 0;
}

int GetMinimumPathFlow(const Graph &graph, int s, int t, const unordered_map<int,int> &parent)
{
    int minimumPathFlow = numeric_limits<int>::max();

    for (int v = t; v != s; v = parent.at(v))
    {
        int u = parent.at(v);

        minimumPathFlow = min(minimumPathFlow, graph.GetEdgeWeight(u,v));
    }

    return minimumPathFlow;
}

int FordFulkersonAlgorithm(const Graph &graph, int source, int sink)
{
    int maximumFlow = 0;
    Graph residualNetwork = graph;
    unordered_map<int,int> parent;

    while (BFS(residualNetwork, source, sink, parent))
    {
        int minimumPathFlow = GetMinimumPathFlow(residualNetwork, source, sink, parent);

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];

            residualNetwork.UpdateEdge(u, v, -minimumPathFlow);
            residualNetwork.UpdateEdge(v, u, minimumPathFlow);
        }

        maximumFlow += minimumPathFlow;
    }

    return maximumFlow;
}

int main()
{
    Graph graph = ReadGraph();

    int source = GetSource(graph);
    int sink = GetSink(graph);

    cout << "The maximal flow is: " << FordFulkersonAlgorithm(graph, source, sink) << endl;

    return 0;
}


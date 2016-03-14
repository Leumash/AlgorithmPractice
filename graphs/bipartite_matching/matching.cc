/*
Problem Description: Find the largest set of edges E' from E such that each vertex in V is incident to at most one edge of E'.

1. First test to see if bipartite.
2. The standard algorithm for bipartite matching is based on network flow.

*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
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
        void AddEdge(int start, int destination, int weight);
        vector<Edge> GetEdges(int vertex) const;
        vector<int> GetVertices() const;
        void UpdateEdge(int s, int t, int toAdd);
    private:
        unordered_map<int,vector<Edge>> adjacencyList;
};

void Graph::UpdateEdge(int s, int t, int toAdd)
{
    if (adjacencyList.count(s) > 0)
    {
        for (Edge &edge : adjacencyList[s])
        {
            if (edge.vertex == t)
            {
                edge.weight += toAdd;
            }
        }
    }
}

void Graph::AddVertex(int vertex)
{
    if (adjacencyList.count(vertex) == 0)
    {
        adjacencyList[vertex] = vector<Edge>();
    }
}

void Graph::AddEdge(int start, int destination, int weight = 1)
{
    AddVertex(start);
    AddVertex(destination);

    adjacencyList[start].push_back(Edge(destination, weight));
}

vector<Edge> Graph::GetEdges(int vertex) const
{
    if (adjacencyList.count(vertex) > 0)
    {
        return adjacencyList.at(vertex);
    }
    else
    {
        return vector<Edge>();
    }
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

Graph ReadGraph()
{
    Graph graph;
    int vertex;
    int neighbor;
    string line;

    while (cin >> vertex)
    {
        graph.AddVertex(vertex);

        getline(cin, line);

        stringstream ss;

        ss << line;

        while (ss >> neighbor)
        {
            graph.AddEdge(vertex, neighbor);
        }
    }

    return graph;
}

bool IsVisited(int vertex, const unordered_map<int,bool> &vertexToColor)
{
    return vertexToColor.count(vertex) > 0;
}

bool IsSameColor(int u, int v, const unordered_map<int,bool> &vertexToColor)
{
    return vertexToColor.at(u) == vertexToColor.at(v);
}

bool BFS(const Graph &graph, int s, unordered_map<int,bool> &vertexToColor)
{
    queue<int> toVisit;
    toVisit.push(s);
    vertexToColor[s] = false;

    while (!toVisit.empty())
    {
        int currentVertex = toVisit.front();
        toVisit.pop();

        vector<Edge> neighbors = graph.GetEdges(currentVertex);

        for (Edge edge : neighbors)
        {
            if (IsVisited(edge.vertex, vertexToColor))
            {
                if (IsSameColor(currentVertex, edge.vertex, vertexToColor))
                {
                    return false;
                }
            }
            else
            {
                toVisit.push(edge.vertex);
                vertexToColor[edge.vertex] = !vertexToColor[currentVertex];
            }
        }
    }

    return true;
}

bool IsBipartite(const Graph &graph, vector<int> &left, vector<int> &right)
{
    unordered_map<int,bool> vertexToColor;   // Doubles as visited

    vector<int> vertices = graph.GetVertices();

    for (int vertex : vertices)
    {
        if (!IsVisited(vertex, vertexToColor))
        {
            // If vertex has not been visited, run BFS while coloring the nodes

            if (!BFS(graph, vertex, vertexToColor))
            {
                return false;
            }
        }
    }

    for (const auto &vToC : vertexToColor)
    {
        if (vToC.second == false)
        {
            left.push_back(vToC.first);
        }
        else
        {
            right.push_back(vToC.first);
        }
    }

    return true;
}

void GetUniqueSourceAndSink(const Graph &graph, int &source, int &sink)
{
    vector<int> vertices = graph.GetVertices();

    while (find(vertices.begin(), vertices.end(), source) != vertices.end())
    {
        source = rand();
    }

    vertices.push_back(source);

    while (find(vertices.begin(), vertices.end(), sink) != vertices.end())
    {
        sink = rand();
    }
}

void AddVerticesToNetworkFlow(Graph &networkFlow, const Graph &graph, int source, int sink)
{
    networkFlow.AddVertex(source);
    networkFlow.AddVertex(sink);

    for (int vertex : graph.GetVertices())
    {
        networkFlow.AddVertex(vertex);
    }
}

void AddEdgesToNetworkFlow(Graph &networkFlow, const Graph &graph, int source, int sink, const vector<int> &left, const vector<int> &right)
{
    for (int vertex : left)
    {
        networkFlow.AddEdge(source, vertex, 1);
    }

    for (int vertex : right)
    {
        networkFlow.AddEdge(vertex, sink, 1);
    }

    for (int vertex : left)
    {
        for (Edge edge : graph.GetEdges(vertex))
        {
            networkFlow.AddEdge(vertex, edge.vertex, 1);
        }
    }
}

Graph ReduceBipartiteMatchingToNetworkFlow(const Graph &graph, const vector<int> &left, const vector<int> &right, int &source, int &sink)
{
    Graph networkFlow;

    GetUniqueSourceAndSink(graph, source, sink);

    AddVerticesToNetworkFlow(networkFlow, graph, source, sink);

    AddEdgesToNetworkFlow(networkFlow, graph, source, sink, left, right);

    return networkFlow;
}

int GetMinimumPathFlow(int s, int t, const Graph &graph, const unordered_map<int,int> &parent)
{
    int minimumPathFlow = numeric_limits<int>::max();

    for (int v = t; v != s; v = parent.at(v))
    {
        int u = parent.at(v);

        for (Edge edge : graph.GetEdges(u))
        {
            if (edge.vertex == v)
            {
                minimumPathFlow = min(minimumPathFlow, edge.weight);
            }
        }
    }

    return minimumPathFlow;
}

bool BFS(const Graph &graph, int s, int t, unordered_map<int,int> &parent)
{
    parent.clear();

    queue<int> toVisit;
    unordered_set<int> visited;

    toVisit.push(s);
    visited.insert(s);

    while (!toVisit.empty())
    {
        int currentVertex = toVisit.front();
        toVisit.pop();

        for (const Edge &edge : graph.GetEdges(currentVertex))
        {
            if (visited.count(edge.vertex) == 0 && edge.weight > 0)
            {
                toVisit.push(edge.vertex);
                visited.insert(edge.vertex);
                parent[edge.vertex] = currentVertex;
            }
        }
    }

    return parent.count(t) > 0;
}

int FordFulkersonAlgorithm(const Graph &graph, int s, int t, Graph &residualNetwork)
{
    int maximumFlow = 0;
    residualNetwork = graph;
    unordered_map<int,int> parent;

    while (BFS(residualNetwork, s, t, parent))
    {
        int minimumPathFlow = GetMinimumPathFlow(s, t, residualNetwork, parent);

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];

            residualNetwork.UpdateEdge(u,v, -minimumPathFlow);
            residualNetwork.UpdateEdge(v,u, minimumPathFlow);
        }

        maximumFlow += minimumPathFlow;
    }

    return maximumFlow;
}

void DisplayOutput(int maximumBipartiteMatching, const Graph &graph, const vector<int> &left)
{
    cout << "Maximum Bipartite Matching: " << maximumBipartiteMatching << endl << endl;

    cout << "Edges: " << endl;

    for (int vertex : left)
    {
        for (const Edge &edge : graph.GetEdges(vertex))
        {
            if (edge.weight == 0)
            {
                cout << vertex << " -> " << edge.vertex << endl;
            }
        }
    }
}

int main()
{
    vector<int> left, right;
    Graph graph = ReadGraph();

    if (!IsBipartite(graph, left, right))
    {
        cout << "Graph is not bipartite!!" << endl;
        exit(1);
    }

    int source, sink;

    Graph networkFlow = ReduceBipartiteMatchingToNetworkFlow(graph, left, right, source, sink);

    Graph residualNetwork;

    int maximumBipartiteMatching = FordFulkersonAlgorithm(networkFlow, source, sink, residualNetwork);

    DisplayOutput(maximumBipartiteMatching, residualNetwork, left);

    return 0;
}


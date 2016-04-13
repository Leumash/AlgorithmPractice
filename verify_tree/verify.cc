// Check if a given graph is a tree
// Write a function that returns true if a given undirected graph is tree and false otherwise.

// Runtime: O(|V|)

// Strategy: Run BFS and check for cycles and if the graph is connected

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Graph
{
    public:
        vector<int> GetVertices() const;
        const vector<int>& GetEdges(int v) const;
    private:
        unordered_map<int,vector<int>> adjacencyList;
};

vector<int> Graph::GetVertices() const
{
    vector<int> vertices;

    for (const auto &vertexAndNeighbors : adjacencyList)
    {
        vertices.push_back(vertexAndNeighbors.first);
    }

    return vertices;
}

const vector<int>& Graph::GetEdges(int v) const
{
    return adjacencyList.at(v);
}

bool IsTree(const Graph &graph)
{
    // 1. Check for cycles
    // 2. Check if connected

    vector<int> vertices = graph.GetVertices();

    if (vertices.size() <= 1)
    {
        return true;
    }

    queue<int> toVisit;
    unordered_set<int> visited;
    unordered_map<int,int> parents;

    toVisit.push(vertices[0]);
    visited.insert(vertices[0]);

    while (!toVisit.empty())
    {
        int currentVertex = toVisit.front();
        toVisit.pop();

        for (int neighbor : graph.GetEdges(currentVertex))
        {
            if (visited.count(neighbor) > 0 && parents[neighbor] != currentVertex)
            {
                return false;
            }

            if (visited.count(neighbor) == 0)
            {
                toVisit.push(neighbor);
                visited.insert(neighbor);
                parents[neighbor] = currentVertex;
            }
        }
    }

    if (visited.size() < vertices.size())
    {
        return false;
    }

    return true;
}

int main()
{
    return 0;
}


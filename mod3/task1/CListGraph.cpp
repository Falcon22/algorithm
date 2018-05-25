#include "CListGraph.h"

CListGraph::CListGraph(int n) : adjacencyList(n) {};

CListGraph::CListGraph(const IGraph &other) : CListGraph(other.VerticesCount()) {
    for (int i = 0; i < other.VerticesCount(); i++) {
        std::vector<int> verticies;
        GetNextVertices(i, verticies);
        for (auto j : verticies) {
            AddEdge(i, j);
        }
    }
}

void CListGraph::AddEdge(int from, int to) {
    adjacencyList[from].push_front(to);
}

void CListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    vertices.clear();

    for (auto i : adjacencyList[vertex]) {
        vertices.push_back(i);
    }
}

int CListGraph::VerticesCount() const {
    return to<int>(adjacencyList.size());
}

void CListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    vertices.clear();

    for (int i = 0; i < VerticesCount(); i++) {
        for (auto j : adjacencyList[i]) {
            if (vertex == j) {
                vertices.push_back(i);
            }
        }
    }
}



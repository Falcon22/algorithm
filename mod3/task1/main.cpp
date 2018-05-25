#include <iostream>
#include "CListGraph.h"

int main() {
    CListGraph graph(5);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(0, 4);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(2, 4);

    std::vector<int> v;
    graph.GetPrevVertices(4, v);
    for (auto i : v) {
        std::cout << i << " ";
    }
    return 0;
}
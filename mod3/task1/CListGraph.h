//
// Created by Falcon on 25.05.2018.
//

#ifndef TASK1_CLISTGRAPH_H
#define TASK1_CLISTGRAPH_H

#include "IGraph.h"
#include <vector>
#include <list>

class CListGraph : public IGraph {
public:
    explicit CListGraph(int n);
    explicit CListGraph(const IGraph& other);

    virtual void AddEdge(int from, int to) override ;

    virtual int VerticesCount() const override ;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
    std::vector<std::list<int>> adjacencyList;

    bool isValidIndex(int index) const {
        return 0 <= index && index < to<int>(adjacencyList.size());
    }
};

#endif //TASK1_CLISTGRAPH_H

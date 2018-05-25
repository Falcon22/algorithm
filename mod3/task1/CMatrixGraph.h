#ifndef TASK1_CMATRIXGRAPH_H
#define TASK1_CMATRIXGRAPH_H

#include "IGraph.h"
#include <cassert>
#include <vector>

class CMatrixGraph : public IGraph {
public:
    explicit CMatrixGraph(int n);
    explicit CMatrixGraph(const IGraph& other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticiesCount() const override;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
    std::vector<std::vector<int>> adjacencyMartix;

    bool isValidIndex(int index) const {
        return 0 <= index && index < to<int>(adjacencyMartix.size());
    }
};


#endif //TASK1_CMATRIXGRAPH_H

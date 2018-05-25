//
// Created by Falcon on 25.05.2018.
//

#ifndef TASK1_IGRAPH_H
#define TASK1_IGRAPH_H

#include <cassert>
#include <vector>

template <class To, class From>
To to(From from)
{
    To to = static_cast<To>(from);
    assert(static_cast<From>(to) == from);
    return to;
}

struct IGraph {
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};


#endif //TASK1_IGRAPH_H

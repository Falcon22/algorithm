#include <iostream>
#include <vector>
#include <list>
#include <set>

#define MAXDIST 100000001

struct Edge {
public:
  Edge(int to, int w) : to(to), w(w) {};
  int to;
  int w;
};

void dijkstra(int v, std::vector<std::vector<Edge>>& graph, std::vector<int>& d) {
  std::set<std::pair<int, int>> q;

  for (int i = 0; i < graph.size(); i++) {
    if (i == v) {
      d[i] = 0;
    } else {
      d[i] = MAXDIST;
    }
    q.insert(std::make_pair(d[i], i));
  }
  
  while (!q.empty()) {
    std::pair<int, int> vMin = *q.begin();
    q.erase(q.begin());
    for (auto i : graph[vMin.second]) {
      if (d[i.to] > d[vMin.second] + i.w) {
        q.erase(q.find(std::make_pair(d[i.to], i.to)));
        d[i.to] = d[vMin.second] + i.w;
        q.insert(std::make_pair(d[i.to], i.to));
      }
    }
  }
}

int main(int argc, const char * argv[]) {
  int n, m, from, to, w, u, v;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n);
  std::vector<int> d(n);
  
  for (int i = 0; i < m; i++) {
    std::cin >> from >> to >> w;
    Edge newEdge1(to, w);
    Edge newEdge2(from, w);
    graph[from].push_back(newEdge1);
    graph[to].push_back(newEdge2);
  }
  
  std::cin >> u >> v;
  
  dijkstra(u, graph, d);
  std::cout << d[v] << std::endl;
  return 0;
}

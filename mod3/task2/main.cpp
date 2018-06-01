#include <iostream>
#include <vector>
#include <queue>

#define MAXDIST 100000

int bfs(int u, int w, std::vector<std::vector<int>>& graph) {
  std::vector<bool> visited(graph.size(), false);
  std::queue<int> q;
  std::vector<int> dist(graph.size(), MAXDIST);
  std::vector<int> paths(graph.size(), 0);
  paths[u] = 1;
  for (auto i : graph[u]) {
    paths[i] = 1;
  }
  q.push(u);
  dist[u] = 0;
  
  while (!q.empty()) {
    int v = q.front();
    q.pop();
      visited[v] = true;
      for (auto i : graph[v]) {
        if (dist[v] + 1 < dist[i]) {
          dist[i] = dist[v] + 1;
          paths[i] = paths[v];
        } else if ((dist[v] + 1) == dist[i]) {
          paths[i] += paths[v];
        }
        if (!visited[i]) {
          q.push(i);
          visited[i] = true;
        }
      }
  }
  
  return paths[w];
}

int main(int argc, const char * argv[]) {
  int n, v, u, w, from, to;
  std::cin >> v >> n;
  std::vector<std::vector<int>> graph(v);
  for (int i = 0; i < n; i++) {
    std::cin >> from >> to;
    graph[from].push_back(to);
    graph[to].push_back(from);
  }
  
  std::cin >> w >> u;
  std::cout << bfs(w, u, graph);
  return 0;
}

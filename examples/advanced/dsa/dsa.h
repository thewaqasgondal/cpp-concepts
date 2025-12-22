#pragma once
#include <vector>
#include <queue>
#include <limits>
#include <iostream>

using Node = int;
using Weight = int;
using AdjList = std::vector<std::vector<std::pair<Node, Weight>>>;

inline std::vector<Weight> dijkstra(const AdjList &g, Node src) {
    const Weight INF = std::numeric_limits<Weight>::max() / 4;
    std::vector<Weight> dist(g.size(), INF);
    dist[src] = 0;
    using P = std::pair<Weight, Node>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto &e : g[u]) {
            Node v = e.first; Weight w = e.second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

inline void bfs(const AdjList &g, Node start) {
    std::vector<int> seen(g.size());
    std::queue<Node> q; q.push(start); seen[start]=1;
    std::cout << "BFS order:";
    while(!q.empty()){
        Node u=q.front(); q.pop();
        std::cout << ' ' << u;
        for (auto &e : g[u]) if(!seen[e.first]){ seen[e.first]=1; q.push(e.first); }
    }
    std::cout << '\n';
}

inline void dfs_rec(const AdjList &g, Node u, std::vector<int> &seen) {
    seen[u]=1; std::cout << ' ' << u;
    for (auto &e: g[u]) if(!seen[e.first]) dfs_rec(g, e.first, seen);
}

inline void dfs(const AdjList &g, Node start) {
    std::vector<int> seen(g.size());
    std::cout << "DFS order:";
    dfs_rec(g, start, seen);
    std::cout << '\n';
}

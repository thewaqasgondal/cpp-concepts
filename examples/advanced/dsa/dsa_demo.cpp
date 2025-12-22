#include "dsa.h"

int main(){
    // Graph with 6 nodes
    AdjList g(6);
    auto add = [&](int u,int v,int w){ g[u].push_back({v,w}); g[v].push_back({u,w}); };
    add(0,1,7); add(0,2,9); add(0,5,14);
    add(1,2,10); add(1,3,15);
    add(2,3,11); add(2,5,2);
    add(3,4,6); add(4,5,9);

    std::cout << "Dijkstra from node 0:\n";
    auto dist = dijkstra(g, 0);
    for (size_t i=0;i<dist.size();++i){
        std::cout << "  dist["<<i<<"] = " << dist[i] << '\n';
    }

    bfs(g, 0);
    dfs(g, 0);
    return 0;
}

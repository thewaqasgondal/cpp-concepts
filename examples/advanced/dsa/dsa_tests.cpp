#include <cassert>
#include "dsa.h"

void test_dijkstra_simple(){
    AdjList g(4);
    auto add=[&](int u,int v,int w){ g[u].push_back({v,w}); g[v].push_back({u,w}); };
    add(0,1,1); add(1,2,2); add(0,2,4); add(2,3,1);
    auto dist=dijkstra(g,0);
    assert(dist[0]==0);
    assert(dist[1]==1);
    assert(dist[2]==3);
    assert(dist[3]==4);
}

int main(){
    test_dijkstra_simple();
    return 0;
}

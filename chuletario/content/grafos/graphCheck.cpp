bool graphCheck(int u, vvi &adjList, vi &dfs_num, vi &dfs_parent) {
    bool cycle = false;
    dfs_num[u] = EXPLORED;
    for (int j = 0; j < adjList[u].size(); j++) {
        int v = adjList[u][j];
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            // Pon cycle |= si quieres parar de explorar el grafo en cuanto se detecte un ciclo.
            cycle = graphCheck(v, adjList, dfs_num, dfs_parent) || cycle;
        } else if (dfs_num[v] == EXPLORED)
            if (v != dfs_parent[u]) // Back edge, graph is cyclic (quita esta linea si el grafo es dirigido).
                cycle = true; // Haz return si quieres parar de explorar el grafo en cuanto se detecte un ciclo.
        else if (dfs_num[v] == VISITED) {
            // Forward cross edge.
        }
    }
    dfs_num[u] = VISITED;

    return cycle;
}

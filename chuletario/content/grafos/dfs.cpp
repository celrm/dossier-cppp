void dfs(int u, vvi &adjList, vi &dfs_num, vi &topo) {
    dfs_num[u] = 1;
    for (int v : adjList[u]) {
        if (dfs_num[v] == 0)
            dfs(v, adjList, dfs_num, topo);
    }
    topo.push_back(u); // Read topo in reverse order.
}

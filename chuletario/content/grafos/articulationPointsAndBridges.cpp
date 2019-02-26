vvi adjList;
set<ii> bridges;
vi dfs_num, dfs_low, dfs_parent;
vector<bool> ap;
int dfsCounter, dfsRoot, rootChildren;

void findAp(int u) {
    dfs_num[u] = dfs_low[u] = dfsCounter++;
    for (int j = 0; j < adjList[u].size(); j++) {
        int v = adjList[u][j];
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            if (u == dfsRoot) rootChildren++;

            findAp(v);

            ap[u] = ap[u] | (dfs_low[v] >= dfs_num[u]);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (dfs_parent[v] != u) // A back edge.
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

void findBridges(int u) {
    dfs_num[u] = dfs_low[u] = dfsCounter++;
    for (int j = 0; j < adjList[u].size(); j++) {
        int v = adjList[u][j];
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            
            findBridges(v);

            if (dfs_low[v] > dfs_num[u])
                bridges.insert(ii(min(u, v), max(u, v)));
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) // A back edge.
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

// Como usarlos
int main() {
    dfsCounter = 0;
    dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0); dfs_parent.assign(V, 0);
    for (int u = 0; u < V; u++)
        if (dfs_num[u] = UNVISITED) {
            dfsRoot = u; rootChildren = 0; findAp(u);
            ap[dfsRoot] = rootChildren > 1;
        }
}

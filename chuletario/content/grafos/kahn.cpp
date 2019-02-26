bool kahn(vvi &adjList, vi &topo) {
    vi inDeg(adjList.size(), 0);
    
    for (int u = 0; u < adjList.size(); u++)
        for (int v = 0; v < adjList[u].size(); v++)
            inDeg[adjList[u][v]]++;
    
    queue<int> q;
    for (int u = 0; u < inDeg.size(); u++)
        if (inDeg[u] == 0) q.push(u);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v = 0; v < adjList[u].size(); v++)
            if (--inDeg[adjList[u][v]] == 0) q.push(adjList[u][v]);
    }
    
    for (int u = 0; u < inDeg.size(); u++)
        if (inDeg[u] != 0) return true;
    return false;
}


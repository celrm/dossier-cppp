void eulerTour(list<int>::iterator it, int u) {
    for (int j = 0; j < adjList[u].size(); j++) {
        ii v = adjList[u][j];
        if (v.second == 1) {
            adjList[u][j].second = 0;
            for (int k = 0; k < adjList[v.first].size(); k++) {
                ii e = adjList[v.first][k];
                if (e.second == 1 && e.first == u) {
                    adjList[v.first][k].second = 0;
                    break;
                }
            }
            eulerTour(cyc.insert(it, u), v.first);
        }
    }
}

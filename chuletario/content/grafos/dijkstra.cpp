void dijkstra(int s, vector<vii> const& grafo, vi &dist) {
    dist.assign(adjList.size(), numeric_limits<int>::max());
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0,s});
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (auto v : grafo[u]) {
            if (dist[u] + v.first < dist[v.second]) {
                dist[v.second] = dist[u] + v.first;
               pq.push({dist[v.second], v.second});
            }
        }
    }
}

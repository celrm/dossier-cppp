vi color;

bool is_bipartite(vvi &adjList, int s, int &white, int &black) {
    queue<int> q;
    q.push(s);
    color[s] = 0;
    black = 1;
    white = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adjList[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                if (color[v] == 0) black++;
                else white++;
                q.push(v);
            } else if (color[v] == color[u]) return false;
        }
    }
    return true;
}

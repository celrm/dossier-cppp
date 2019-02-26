bool bellman_ford(int s, vector<vector<pair<int,int>>> const& grafo,
                  vector<int> & dist, vector<bool> & en_ciclo) {
   dist.assign(grafo.size(), INF);
   en_ciclo.assign(grafo.size(), false);
   dist[s] = 0;
   bool changed = true;
   for (int i = 0; i < grafo.size() && changed; ++i) {
      changed = false;
      for (int u = 0; u < grafo.size(); ++u) {
         for (auto & a : grafo[u]) {
            if (dist[a.first] > dist[u] + a.second) {
               dist[a.first] = dist[u] + a.second;
               changed = true;
               if (i == grafo.size() - 1) en_ciclo[a.first] = true;
            }
         }
      }
   }
   return changed;
}

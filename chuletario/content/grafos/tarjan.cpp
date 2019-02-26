const int UNVISITED = -1;
vector<int> S, dfs_num, dfs_low, cur_scc, component;
vector<vector<int>> grafo, sccs;
int V, dfsCounter = 0;

void tarjanSCC(int u) {
   dfs_num[u] = dfs_low[u] = dfsCounter++;
   cur_scc[u] = 1;
   S.push_back(u);
   
   for (int v : grafo[u]) {
      if (dfs_num[v] == UNVISITED)
         tarjanSCC(v);
      if (cur_scc[v] == 1) // El nodo v ha sido visitado, pero esta en la misma SCC que u? Podria tratarse de un forward edge a otra SCC.
         dfs_low[u] = min(dfs_low[u], dfs_low[v]);
   }
   
   // inserta aqui u en un vector para generar un reverse toposort si quieres.
   
   if (dfs_low[u] == dfs_num[u]) {
      vector<int> scc;
      int v, nc = (int)sccs.size();
      do {
         v = S.back(); S.pop_back();
         cur_scc[v] = 0;
         scc.push_back(v);
         component[v] = nc;
      } while (u != v);
      sccs.push_back(scc);
   }
}

// hallamos las SCCs (en resuelve())
dfsCounter = 0;
dfs_num.assign(V, UNVISITED); dfs_low.assign(V, 0); cur_scc.assign(V, 0);
component.assign(V, 0); S.clear(); sccs.clear();
for (int i = 0; i < V; ++i)
   if (dfs_num[i] == UNVISITED)
      tarjanSCC(i);


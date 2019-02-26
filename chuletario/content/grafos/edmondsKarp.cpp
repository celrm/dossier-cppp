int V, f, s, t;  // global variables
vector<vector<int>> res; // matriz de adyacencia, con capacidades
vector<vector<int>> grafo; // listas de adyacentes, también los back edges
vector<int> p; // parent

void augment(int v, int minEdge) {  // traverse BFS spanning tree from s to t
   if (v == s) { f = minEdge; return; }  // record minEdge in global var f
   else if (p[v] != -1) {
      augment(p[v], min(minEdge, res[p[v]][v])); // recursive
      res[p[v]][v] -= f; res[v][p[v]] += f;   // update
   }
}

// Edmonds Karp Max Flow O(VE^2)
int edmondsKarp() {
   int mf = 0;    // mf stands for max_flow
   while (1) {
      f = 0;
      // BFS
      vector<bool> marcado(V, false); marcado[s] = true;
      queue<int> q; q.push(s);
      p.assign(V, -1);  // record the BFS spanning tree, from s to t!
      while (!q.empty()) {
         int u = q.front(); q.pop();
         if (u == t) break;      // immediately stop BFS if we already reach sink t
         for (auto v : grafo[u])
            if (res[u][v] > 0 && !marcado[v]) {
               marcado[v] = true;
               q.push(v);
               p[v] = u;
            }
      }
      augment(t, INF);   // find the min edge weight `f' along this path, if any
      if (f == 0) break;      // we cannot send any more flow (`f' = 0), terminate
      mf += f;                // we can still send a flow, increase the max flow!
   }
   return mf;
}


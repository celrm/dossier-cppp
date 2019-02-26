int kosaraju(vector<vector<int>> &adjList) {
   vector<int> dfs_num(adjList.size(), 0), topo;
   
   for (int u = 0; u < adjList.size(); u++)
      if (dfs_num[u] == 0)
         dfs(u, adjList, dfs_num, topo);
   
   // compute transpose graph
   vector<vector<int>> adjListT(adjList.size(), {});
   for (int u = 0; u < adjList.size(); u++)
      for (int v : adjList[u])
         adjListT[v].push_back(u);
   
   int scc = 0;
   dfs_num.assign(adjListT.size(), 0);
   for (int i = topo.size() - 1; i >= 0; i--) {
      if (dfs_num[topo[i]] == 0) {
         dfs(topo[i], adjListT, dfs_num, topo);
         scc++;
      }
   }
   return scc;
}


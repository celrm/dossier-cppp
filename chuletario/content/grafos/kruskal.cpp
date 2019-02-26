int kruskal(vector<pair<int, ii>> &edgeList) {
    sort(edgeList.begin(), edgeList.end());
    int mst_cost = 0;
    ufds uf(V);

    for (int i = 0; i < E && uf.numSets != 1; i++) {
        pair<int, ii> front = edgeList[i];
        if (!uf.isSameSet(front.second.first, front.second.second)) {
            mst_cost += front.first;
            uf.unionSet(front.second.first, front.second.second);
        }
    }

    if (uf.numSets != 1) return INT_MAX; // this graph is not connected
    return mst_cost;
}

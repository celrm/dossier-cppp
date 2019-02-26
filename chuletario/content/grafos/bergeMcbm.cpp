int M, N; // M parte izquierda, N parte derecha
vector<unordered_set<int>> grafo; // dirigido, tamaño M   sets para poder borrar
vector<int> match, vis;

int aug(int l) { // Devuelve 1 si encuentra un augmenting path para el matching M representado en match.
    if (vis[l]) return 0;
    vis[l] = 1;
    for (auto r : grafo[l]) {
         if (match[r] == -1 || aug(match[r])) {
            match[r] = l;
            return 1;
        }
    }
    return 0;
}

int berge_mcbm() {
    int mcbm = 0;
    match.assign(N + M, -1);
    vis.assign(M, 0);
    for (int l = 0; l < M; l++) {
        vis.assign(M, 0);
        mcbm += aug(l);
    }
    return mcbm;
}

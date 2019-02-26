
struct ufds {
    int numSets;
    vector<int> p;
    
    ufds(int N) : numSets(N), p(N, -1) { }
    
    int findSet(int i) { // finds and path compresses if possible
        return (p[i] < 0) ? i : (p[i] = findSet(p[i]));
    }
    
    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
    
    void unionSet(int i, int j) {
        int x = findSet(i), y = findSet(j);
        if (x == y) return;
        if (p[x] < p[y]) {
            p[x] += p[y];
            p[y] = x;
        } else {
            p[y] += p[x];
            p[x] = y;
        }
        --numSets;
    }
    
    int sizeSet(int i) { // returns size of the set to which element i belongs
        return -p[findSet(i)];
    }
};


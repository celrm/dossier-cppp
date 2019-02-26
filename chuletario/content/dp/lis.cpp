vi lis(const vi &a) {
    vi L, L_id, P;
    L.assign(a.size(), 0);
    L_id.assign(a.size(), 0);
    P.assign(a.size(), -1);
    
    int lis_len = 0, lis_end = 0;
    for (int i = 0; i < a.size(); i++) {
        int pos = lower_bound(L.begin(), L.begin() + lis_len, a[i]) - L.begin();
        L[pos] = a[i];
        L_id[pos] = i;
        P[i] = pos ? L_id[pos-1] : -1;
        if (pos == lis_len) {
            lis_len++;
            lis_end = i;
        }
    }
    
    vi sol;
    stack<int> s;
    int x = lis_end;
    for (; P[x] >= 0; x = P[x]) s.push(a[x]);
    sol.push(a[x]);
    for (; !s.empty(); s.pop()) sol.push(s.top());
    
    return sol;
}

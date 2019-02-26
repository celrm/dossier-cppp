sort(v.begin(), v.end(), cmp());

int i = 0;
while (i < v.size() && v[i].second < 0) i++;

vii sol;
ii p = ii(0, 0);
while (i < v.size() && p.second < M) {
    ii q = v[i];

    if (q.first > p.second)
        break;

    while (i < v.size() && v[i].first <= p.second) {
        if (v[i].second > q.second)
            q = v[i];

        i++;
    }

    sol.push_back(q);
    p = q;
 }

if (sol.size() > 0 && sol[sol.size() - 1].second >= M) { // OK
 } else { // No se puede recubrir el intervalo [0, M]

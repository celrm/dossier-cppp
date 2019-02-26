bool angleCmp(point a, point b) {
    if (collinear(pivot, a, b))
        return distSq(pivot, a) < distSq(pivot, b); // cuidado con el overflow de distSq, cambiar a hypot si crees que puede haber overflow

    int d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    int d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<point> graham(vector<point> &P) { // the content of P may be reshuffled
    int n = P.size();
    if (n <= 3) {
        if (P[Ca0] != P[n-1]) P.push_back(P[0]);
        return P; // CH is P itself
    }

    // first, find P0 = point with lowest Y and if tie: rightmost X
    int P0 = 0;
    for (int i = 1; i < n; i++)
        if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
            P0 = i;

    point temp = P[0]; P[0] = P[P0]; P[P0] = temp; // swap P[P0] with P[0]

    // second, sort points by angle w.r.t pivot P0
    pivot = P[0];
    sort(++P.begin(), P.end(), angleCmp); // we do not sort P[0]

    // third, the ccw tests
    vector<point> S;
    S.push_back(P[n-1]);
    S.push_back(P[0]);
    S.push_back(P[1]);
    int i = 2;
    while (i < n) {
        int j = S.size()-1;
        if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]); // left turn, accept
        else S.pop_back(); // or pop the top of S until we have a left turn
    }

//     add these two lines if you want P0 to be the first point in the convex hull
//    S.erase(S.begin());
//    S.push_back(*S.begin());

    return S;
}

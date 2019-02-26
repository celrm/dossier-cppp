bool inPolygon(point pt, const vector<point> &P) {
    if (P.size() <= 3) return false;
    double sum = 0;
    for (int i = 0; i < P.size() - 1; i++) {
        if (ccw(pt, P[i], P[i + 1])) sum += angle(P[i], pt, P[i + 1]);
        else sum -= angle(P[i], pt, P[i + 1]);
    }
    return fabs(fabs(sum) - 2*PI) < EPS; // sum sera negativo si los vertices se recorrieron clockwise
}

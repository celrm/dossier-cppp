double area(const vector<point> &P) {
    int result = 0, x1, y1, x2, y2;
    for (int i = 0; i < P.size()-1; i++) {
        x1 = P[i].x; x2 = P[i+1].x;
        y1 = P[i].y; y2 = P[i+1].y;
        result += (x1 * y2 - x2 * y1);
    }
    return ((double) abs(result)) / 2;
}

double perimeter(vector<point> &P) {
    double result = 0.0;
    for (int i = 0; i < P.size()-1; i++) // remember that P[0] == P[n-1]
        result += dist(P[i], P[i+1]);
    return result;
}

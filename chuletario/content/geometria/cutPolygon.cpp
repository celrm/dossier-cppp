// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
    double a = B.y - A.y, b = A.x - B.x, c = B.x * A.y - A.x * B.y;
    double u = fabs(a * p.x + b * p.y + c), v = fabs(a * q.x + b * q.y + c);
    return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u + v));
}

// cuts polygon Q along the line formed by point a -> point b. Q[0]==Q.back()
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
    vector<point> P;
    for (int i = 0; i < Q.size(); i++) {
        double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
        if (i != Q.size() - 1) left2 = cross(toVec(a, b), toVec(a, Q[i + 1]));
        if (left1 > -EPS) P.push_back(Q[i]);       // Q[i] is on the left of ab
        if (left1 * left2 < -EPS)        // edge (Q[i], Q[i+1]) crosses line ab
            P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b));
    }
    if (!P.empty() && !(P.back() == P.front()))
        P.push_back(P.front());        // make P's first point = P's last point
    return P;
}

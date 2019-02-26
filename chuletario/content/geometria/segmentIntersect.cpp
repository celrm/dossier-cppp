struct segment {
    point p;
    vec r;

    segment() { }
    segment(point a, point b) {
        p = a;
        r = toVec(a, b);
    }
};

bool intersect(segment a, segment b, point &x, bool &collinear) {
    vec r = a.r, s = b.r;
    point p = a.p, q = b.p;
    vec pq = toVec(p, q);
    double pqxr = cross(pq, r), rxs = cross(r, s);
    bool parallel = eq(rxs, 0);
    collinear = parallel && eq(pqxr, 0);
    if (collinear) {
        double t0 = dot(pq, r) / dot(r, r);
        double t1 = t0 + dot(s, r) / dot(r, r);
        if (lt(dot(s, r), 0)) swap(t0, t1);
        
        return leq(max(t0, 0.0), min(t1, 1.0));
    } else if (parallel) return false;
    else {
        double t = cross(pq, s) / cross(r, s), u = cross(pq, r) / cross(r, s);
        x = translate(p, scale(r, t));
        
        return leq(0, t) && leq(t, 1) && leq(0, u) && leq(u, 1);
    }
}

struct line {
    double a, b, c; // ax + by + c = 0

    bool operator== (const line &l2) {
        return (a == l2.a && b == l2.b && c == l2.c);
    }
};

bool areParallel(line l1, line l2) {
    return l1.a == l2.a && l1.b == l2.b;
}

line pointsToLine(point p, point q) {
    line l;
    if (p.x == q.x) {
        l.a = 1; l.b = 0; l.c = -p.x;
    } else {
        l.a = (q.y - p.y) / (p.x - q.x);
        l.b = 1;
        l.c = -(l.a * p.x) - p.y;
    }
    return l;
}

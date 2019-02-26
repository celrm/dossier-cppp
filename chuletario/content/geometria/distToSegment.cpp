/**
 * Returns the distance from p to the segment defined by two points a and b.
 * The closest point to p on the segment is stored in c.
 * O(1)
 * @param p
 * @param a
 * @param b
 * @param c
 * @return 
 */
double distToSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) {
        c = point(a.x, a.y);
        return dist(p, a);
    } else if (u > 1.0) {
        c = point(b.x, b.y);
        return dist(p, b);
    } else return distToLine(p, a, b, c);
}

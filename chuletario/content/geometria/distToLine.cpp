/**
 * Returns the distance from p to the line defined by two distinct points a and b.
 * The closest point to p on the line is stored in c.
 * O(1)
 * @param p
 * @param a
 * @param b
 * @param c
 * @return 
 */
double distToLine(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

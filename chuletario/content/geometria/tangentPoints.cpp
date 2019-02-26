void tangentPoints(point p, double r, point pt[]) {
    double p0 = p.x, p1 = p.y;
    double den = p0*p0 + p1*p1;
    double dis = sqrt(p0*p0 + p1*p1 - r*r);
    pt[0] = point((p0*r*r - dis*p1*r)/den, (p1*r*r + dis*p0*r)/den);
    pt[1] = point((p0*r*r + dis*p1*r)/den, (p1*r*r - dis*p0*r)/den);
}

point center(point p1, point p2, point p3) {
    double c1n = 0.5*((p1.y - p3.y)*p2.y*p2.y + p1.x*p1.x*p3.y - p2.x*p2.x*p3.y + p1.y*p1.y*p3.y + (p2.x*p2.x - p3.x*p3.x - p3.y*p3.y)*p1.y - (p1.x*p1.x - p3.x*p3.x + p1.y*p1.y - p3.y*p3.y)*p2.y);
    double c1d = (p2.x - p3.x)*p1.y - (p1.x - p3.x)*p2.y + p1.x*p3.y - p2.x*p3.y;

    double c2n = -0.5*((p1.x - p3.x)*p2.x*p2.x + p1.x*p1.x*p3.x - (p2.x - p3.x)*p1.y*p1.y + (p1.x - p3.x)*p2.y*p2.y - (p3.x*p3.x + p3.y*p3.y)*p1.x - (p1.x*p1.x - p3.x*p3.x - p3.y*p3.y)*p2.x);
    double c2d = (p2.x - p3.x)*p1.y - (p1.x - p3.x)*p2.y + p1.x*p3.y - p2.x*p3.y;

    return point(c1n / c1d, c2n / c2d);
}

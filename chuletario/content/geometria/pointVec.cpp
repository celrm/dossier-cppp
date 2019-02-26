#define EPS 1e-9

struct point {
    double x, y;
    point() {x = y = 0.0;}
    point(double _x, double _y) : x(_x), y(_y) {}
    // to sort points lexicographically
    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator != (const point other) const {
        return x != other.x || y != other.y;
    }
};

struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) { }
};

vec toVec(point a, point b) { return vec(b.x-a.x, b.y-a.y); }

vec scale(vec v, double s) { return vec(v.x*s, v.y*s);}

point translate(point p, vec v) { return point(p.x + v.x, p.y + v.y);}

double dot(vec a, vec b) { return a.x*b.x + a.y*b.y;}

double norm_sq(vec v) { return v.x*v.x + v.y*v.y;}

double dist(point p1, point p2) { return hypot(p1.x - p2.x, p1.y - p2.y);}

double distSq(point p1, point p2) { 
    return (p1.x - p2.x)*(p1.x - p2.x)+ (p1.y - p2.y)*(p1.y - p2.y);
}

double angle(point a, point o, point b) { // returns angle aob in rad
   vec oa = toVec(o, a), ob = toVec(o, b);
   return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// para aceptar puntos colineales cambia a >=
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0;
}

bool collinear(point p, point q, point r) {
    return fabs(cross(toVec(p, q)), toVec(p, r)) < EPS;
}

int insideCircle(point p, point c, double r) {
    double eucSq = distSq(p, c);
    double rSq = r*r;
    if (fabs(eucSq - rSq) > EPS && eucSq < rSq) return 0; // inside
    else if (fabs(eucSq - rSq) < EPS) return 1; // border
    else return 2; // outside
}

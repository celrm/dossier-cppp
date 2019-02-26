double cross(point a, point b, point c) { return cross(toVec(a, b), toVec(b, c)); }

// O(log n) Solo para convexos (ordenados ccw)!
bool inConvexPolygon(point q, vector<point> const &p) {
	if (cross(p[0], p[1], q) < 0 || cross(p[p.size() - 2], p[0], q)<0)
		return false;
	int ini = 1, fin = p.size() - 2, mid;
	while (ini != fin - 1) {
		mid = (ini + fin) / 2;
		if (cross(p[0], p[mid], q) < 0) fin = mid;
		else ini = mid;
	}
	if (cross(p[ini], p[fin], q)<0) return false;
	return true;
}

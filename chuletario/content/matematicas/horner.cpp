double horner(vi &pol, double x) {
	double ev = pol[0];
	for (int n = 1; n < pol.size(); n++)
		ev = ev * x + pol[n];
	return ev;
}

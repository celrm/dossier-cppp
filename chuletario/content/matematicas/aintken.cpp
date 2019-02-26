double interpola(vector<double> x, vector<double> y, double t) {
	int n = x.size(), i, j, l;
	double v[n][n];
	for (i = 0; i < n; ++i) v[i][i] = y[i];
	for (l = 2; l <= n; ++l)
	for (i = 0; (j = i + l - 1) < n; ++i)
		// Tengo el polinomio interpolador de [i..j - 1] y [i + 1..j]
		v[i][j] = ((t - x[i])*v[i + 1][j] + (x[j] - t)*v[i][j - 1]) / (x[j] - x[i]);
	return v[0][n - 1];
}

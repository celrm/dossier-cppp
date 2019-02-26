#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;

typedef double tipo; // puede ser util usar rac (de numteor.cpp) 
typedef vector<tipo> row;
typedef vector<row> matrix;

matrix mult(const matrix &a, const matrix &b) {
	int i, j, k, m = a.size(), n = a[0].size(), p = b[0].size();
	matrix c(m);
	for (i = 0; i < m; i++) c[i].resize(p);
	for (i = 0; i < m; i++)
	for (j = 0; j < p; j++) {
		tipo r = 0;
		for (k = 0; k < n; k++)
			r += a[i][k] * b[k][j];
		c[i][j] = r;
	}
	return c;
}

matrix suma(const matrix &a, const matrix &b) {
	int i, j, n = a.size(), m = a[0].size();
	matrix c(n);
	for (i = 0; i < n; i++)
	for (j = 0; j < m; j++)
		c[i].push_back(a[i][j] + b[i][j]);
	return c;
}

matrix eleva(matrix &a, int n) {
	int l = a.size(), i;
	matrix b(l, row(l, 0));
	for (i = 0; i < l; i++) b[i][i] = 1;
	while (n) // el resultado es b*a^n
	if (n & 1) {
		b = mult(b, a);
		n ^= 1;
	}
	else {
		a = mult(a, a);
		n >>= 1;
	}
	return b;
}


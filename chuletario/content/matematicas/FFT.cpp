

#include <complex>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// sign = 1 -> forward transform, sign = -1 -> reverse
void fft(vector<complex<double> > &a, int sign = 1) {
	int n = a.size(); // n should be a power of two
	float theta = 8 * sign * atan(1.0) / n;
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k >(i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int m, mh = 1; (m = mh << 1) <= n; mh = m) {
		int irev = 0;
		for (int i = 0; i < n; i += m) {
			complex<double>  w = exp(complex<double>(0, theta*irev));
			for (int k = n >> 2; k >(irev ^= k); k >>= 1);
			for (int j = i; j < mh + i; ++j) {
				int k = j + mh;
				complex<double>  x = a[j] - a[k];
				a[j] += a[k];
				a[k] = w * x;
			}
		}
	}
	if (sign == -1)	{
		for (i = 0; i < n; i++)
			a[i] /= n;
	}
	return;
}


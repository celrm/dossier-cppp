tipo recur(vector<int> ini, vector<int> coef, int i) {
	int n = ini.size(), j;
	if (i < n) return ini[i];
	matrix m(n, row(n));
	m[0].assign(coef.begin(), coef.end());
	for (j = 1; j < n; j++) m[j][j - 1] = 1;
	m = eleva(m, i - n + 1);
	tipo res = 0;
	for (i = 0; i < n; i++) res += m[0][i] * ini[n - 1 - i];
	return res;
}

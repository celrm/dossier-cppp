

/*
Resuelve el sistema ax  = b, con n ecuaciones y col incógnitas
Está en Z_M, pero cambiando inv[x] por 1/x y poniendo doubles sirve en R
O(n^2*col)
*/
void gauss(vector<vector<int> > & a, vector<int> & b, int n, int col) {
	for (int row = 0; row < n && row < col; row++) {
		int best = row;
		for (int i = row + 1; i < n; i++)
			if (fabs(a[best][row]) < fabs(a[i][row]))
				best = i;
		swap(a[row], a[best]);
		swap(b[row], b[best]);
		for (int i = row + 1; i < col; i++)
			a[row][i] = ((a[row][i] * inv[a[row][row]]) % M + M) % M;
		b[row] = ((b[row] * inv[a[row][row]]) % M + M) % M;
		// a[row][row] = 1;
		for (int i = 0; i < n; i++) {
			int x = a[i][row];
			if (i != row && x != 0) {
				// row + 1 instead of row is an optimization
				for (int j = row + 1; j < col; j++)
					a[i][j] = ((a[i][j] - a[row][j] * x) % M + M) % M;
				b[i] = ((b[i] - b[row] * x) % M + M) % M;
			}
		}
	}
	for (int i = 0; i < b.size(); ++i) {
		b[i] = ((b[i] % M) + M) % M;
	}
	// b is the solution
}


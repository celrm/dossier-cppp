#define error 1e-9

tipo gauss(matrix &m, int &rango, int &rangoamp) {
	int i, j, k, numec = m.size(), numvar = m[0].size() - 1;
	tipo c;

	rango = 0;
	tipo det = 1;
	for (j = 0; j <= numvar; j++) {
		tipo mayor = 0;
		int l = -1;
		// Elige el mayor pivote
		for (i = rango; i<numec; i++) if (l < 0 || abs(m[i][j]) > mayor) {
			mayor = abs(m[i][j]);
			l = i;
		}
		if (mayor > error) {
			c = m[l][j];
			if (l != rango) det = -det;
			det *= c;
			for (k = j; k <= numvar; k++) {
				swap(m[l][k], m[rango][k]);
				m[rango][k] = m[rango][k] / c;
			}
			for (i = rango + 1; i < numec; i++) {
				c = m[i][j];
				for (k = j; k <= numvar; k++)
					m[i][k] = m[i][k] - m[rango][k] * c;
			}
			if (j < numvar)
				rango++;
		}
	}
	rangoamp = rango;
	for (i = rango; i < numec; i++)
	if (abs(m[i][numvar]) > error) { rangoamp++; break; }
	if (rango != numec) det = 0;
	return det;
}

void resuelve(const matrix &m, row &sol) {
	int i, j, numec = m.size(), numvar = m[0].size() - 1;
	sol.resize(numvar);
	for (i = numec - 1; i >= 0; i--) {
		tipo c = m[i][numvar];
		for (j = i + 1; j < numvar; j++) c = c - m[i][j] * sol[j];
		sol[i] = c;
	}
}

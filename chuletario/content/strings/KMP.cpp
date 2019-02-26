string t, p; vi b;
int n, m; // n=t.size, m=p.size

void kmpPreprocess() { 
	int i = 0, j = -1; b[0] = -1;
	while (i < m) {
		while (j >= 0 && p[i] != p[j]) j = b[j];
		b[++i]=++j; 
	}
}
vi kmpSearch() { 
    int i = 0, j = 0; 
    vi sol;
	while (i<n) { 
		while (j >= 0 && t[i] != p[j]) j = b[j]; 
		i++; j++; 
		if (j==m) 
			sol.push_back(i-j), j = b[j]; 
	}
	return sol;
}

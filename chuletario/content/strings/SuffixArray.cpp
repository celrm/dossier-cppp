#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef pair<int, int> ii;

#define MAX_N 100010 // O(n log n) -> up to 100 K
char T[MAX_N]; int n;  // input string and length
int RA[MAX_N], tempRA[MAX_N], SA[MAX_N], tempSA[MAX_N], c[MAX_N];               

void countingSort(int k) { // O(n)
	int i, sum, maxi = max(300, n); // up to 255 ASCII chars or length of n
	memset(c, 0, sizeof c);  
	for (i = 0; i < n; i++) 
		c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i]; c[i] = sum; sum += t;
	}
	for (i = 0; i < n; i++) 
		tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
	for (i = 0; i < n; i++) 
		SA[i] = tempSA[i];
}

// Builds Suffix Array for string T. T should end with sth like $
void constructSA() { // O(n log n), can go up to 100000 characters
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = T[i]; 
	for (i = 0; i < n; i++) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {      
		countingSort(k); 
		countingSort(0);      
		tempRA[SA[0]] = r = 0;           
		for (i = 1; i < n; i++)                   
			tempRA[SA[i]] = 
			(RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
		for (i = 0; i < n; i++)                     
			RA[i] = tempRA[i];
		if (RA[SA[n - 1]] == n - 1) break; // optimization
	}
}

int Phi[MAX_N], PLCP[MAX_N], LCP[MAX_N]; 

// Longest Common Prefix: Para cada i, halla la longitud del prefijo mas largo
// que comparte con algun otro sufijo, y lo guarda en LCP[i]
// Para hacerlo en O(n), usa el orden inicial de los sufijos, no el del suffix array,
// y de ahi surgen los arrays auxiliares Phi y PLCP
void computeLCP() { // O(n)
	int i, L;
	Phi[SA[0]] = -1;                                        
	for (i = 1; i < n; i++)                         
		Phi[SA[i]] = SA[i - 1]; 
	for (i = L = 0; i < n; i++) {            
		if (Phi[i] == -1) { PLCP[i] = 0; continue; }           
		while (T[i + L] == T[Phi[i] + L]) L++;     
		PLCP[i] = L;
		L = max(L - 1, 0);                         
	}
	for (i = 0; i < n; i++)                           
		LCP[i] = PLCP[SA[i]];
}

// Longest Repeated Substring: por la definicion de LCP, es el valor maximo de LCP
ii LRS() { // O(n), returns a pair (the LRS length and its index in the SA)
	int i, idx = 0, maxLCP = -1;
	for (i = 1; i < n; i++)                         
		if (LCP[i] > maxLCP)
			maxLCP = LCP[i], idx = i;
	return ii(maxLCP, idx);
}

char P[MAX_N]; /*pattern*/ int m; /*length of pattern*/

// Compara T a partir del indice id con P
int comp(int id) {
	for (int i = 0; i < m; ++i) {
		if (id + i >= n || T[id + i] < P[i]) return -1; // P mayor
		if (T[id + i] > P[i]) return 1; // P menor
	}
	return 0;
}

// Devuelve dos extremos (l, u): todos los S[i], i en [l, u]
// son indices donde aparece el patron P
ii stringMatching() { // O(m log n)
	int lo = 0, hi = n - 1, mid = lo;           
	while (lo < hi) { // binary search lower bound
		mid = (lo + hi) / 2;                              
		int res = strncmp(T + SA[mid], P, m); 
		// int res = comp(SA[mid]) if working with strings
		if (res >= 0) hi = mid; 
		else          lo = mid + 1;           
	}                                     
	if (strncmp(T + SA[lo], P, m) != 0) return ii(-1, -1); // if not found
	ii ans; ans.first = lo;
	lo = 0; hi = n - 1; mid = lo;
	while (lo < hi) { // if lower bound is found, binary search upper bound
		mid = (lo + hi) / 2;
		int res = strncmp(T + SA[mid], P, m); 
		// int res = comp(SA[mid]) if working with strings
		if (res > 0) hi = mid;                              
		else         lo = mid + 1;           
	}                         
	if (strncmp(T + SA[hi], P, m) != 0) hi--;                 // special case
	ans.second = hi;
	return ans;
} // return (lowerbound, upperbound)

int owner(int idx) { return (idx < n - m - 1) ? 1 : 2; }

// Longest Common Substring (entre 2 strings): n = T1.size(), m = T2.size()
// Primero las concatenamos: T = T1$T2#. Construimos el suffix array de esta string.
// Llamamos al LCP, y despues a esto -> coste total O(n log n)
ii LCS() { // O(n), returns  (l: the LCS length, i: its index in the SA), i.e., 
		// solution = T[SA[i]] T[SA[i] + 1] ... T[SA[i] + l - 1]
	int i, idx = 0, maxLCP = -1;
	for (i = 1; i < n; i++)                         
		if (owner(SA[i]) != owner(SA[i - 1]) && LCP[i] > maxLCP)
			maxLCP = LCP[i], idx = i;
	return ii(maxLCP, idx);
}

// Ejemplos de uso:

int main() {
	//printf("Enter a string T below, we will compute its Suffix Array:\n");
	strcpy(T, "GATAGACA");
	n = (int)strlen(T);
	T[n++] = '$';
	// if '\n' is read, uncomment the next line
	//T[n-1] = '$'; T[n] = 0;
	
	constructSA();                                              // O(n log n)
	printf("\nThe Suffix Array of string T = '%s' is shown below (O(n log n) version):\n", T);
	printf("i\tSA[i]\tSuffix\n");
	for (int i = 0; i < n; i++) printf("%2d\t%2d\t%s\n", i, SA[i], T + SA[i]);

	computeLCP();                                                     // O(n)

																	  // LRS demo
	ii ans = LRS();                 // find the LRS of the first input string
	char lrsans[MAX_N];
	strncpy(lrsans, T + SA[ans.second], ans.first);
	printf("\nThe LRS is '%s' with length = %d\n\n", lrsans, ans.first);

	// stringMatching demo
	//printf("\nNow, enter a string P below, we will try to find P in T:\n");
	strcpy(P, "A");
	m = (int)strlen(P);
	// if '\n' is read, uncomment the next line
	//P[m-1] = 0; m--;
	ii pos = stringMatching();
	if (pos.first != -1 && pos.second != -1) {
		printf("%s is found SA[%d..%d] of %s\n", P, pos.first, pos.second, T);
		printf("They are:\n");
		for (int i = pos.first; i <= pos.second; i++)
			printf("  %s\n", T + SA[i]);
	}
	else printf("%s is not found in %s\n", P, T);

	// LCS demo
	//printf("\nRemember, T = '%s'\nNow, enter another string P:\n", T);
	// T already has '$' at the back
	strcpy(P, "CATA");
	m = (int)strlen(P);
	// if '\n' is read, uncomment the next line
	//P[m-1] = 0; m--;
	strcat(T, P);                                                 // append P
	strcat(T, "#");                                    // add '$' at the back
	n = (int)strlen(T);                                           // update n

																  // reconstruct SA of the combined strings
	constructSA();                                              // O(n log n)
	computeLCP();                                                     // O(n)
	printf("\nThe LCP information of 'T+P' = '%s':\n", T);
	printf("i\tSA[i]\tLCP[i]\tOwner\tSuffix\n");
	for (int i = 0; i < n; i++)
		printf("%2d\t%2d\t%2d\t%2d\t%s\n", i, SA[i], LCP[i], owner(SA[i]), T + SA[i]);

	ans = LCS();         // find the longest common substring between T and P
	char lcsans[MAX_N];
	printf("%s\n", T + SA[ans.second]);
	strncpy(lcsans, T + SA[ans.second], ans.first);
	printf("\nThe LCS is '%s' with length = %d\n", lcsans, ans.first);

	return 0;
}

#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef pair<ll, ll> ll_ll;

// Mu es el comienzo, lambda el ciclo.
ii floydCycleFinding(int x0) {
	int tortoise = f(x0), hare = f(f(x0));
	while (tortoise != hare)
		tortoise = f(tortoise), hare = f(f(hare));

	// 2nd part: finding mu, hare and tortoise move at the same speed
	int mu = 0; hare = x0;
	while (tortoise != hare)
		tortoise = f(tortoise), hare = f(hare), mu++;

	// 3rd part: finding lambda, hare moves, tortoise stays
	int lambda = 1; hare = f(tortoise);
	while (tortoise != hare)
		hare = f(hare), lambda++;
	return ii(mu, lambda);
}

void brent(int x0) {
	int power = lambda = 1;
	int tortoise = x0, hare = f(x0);
	while (tortoise != hare) {
		if (power == lambda) {
			tortoise = hare;
			power *= 2;
			lambda = 0;
		}
		hare = f(hare);
		lambda++;
	}

	mu = 0;
	tortoise = hare = x0;
	for (int i = 0; i < lambda; i++)
		hare = f(hare);

	while (tortoise != hare) {
		tortoise = f(tortoise);
		hare = f(hare);
		mu++;
	}
}

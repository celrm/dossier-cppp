#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef map<int, int> mii;
typedef pair<ll, ll> ll_ll;

int mod(int a, int b) { return ((a%b) + b) % b; }

// devuelve q y r, el cociente al hacer la division entera de a entre b, tal que q*b + r = a, con r el unico numero positivo \in [0, b) que cumple la igualdad.
// funciona para todas las combinaciones de signos de a y b.
// es decir, divide como un matematico y no como un programador que trunca la division hacia el 0 (ademas el estandar de C++ no especifica siquiera esto).
div_t euc_div(int a, int d) {
    div_t divT = div(a, d);
    int I = divT.rem >= 0 ? 0 : (d > 0 ? 1 : -1);
    int qE = divT.quot - I;
    int rE = divT.rem + I * d;
    return div_t{qE, rE};
}

bitset<10000000> bs; // 10^7
vector<ll> primes;

// criba de Eratóstenes
void sieve() {
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i < bs.size(); i++)
	if (bs[i]) {
		for (ll j = i * i; j < bs.size(); j += i) bs[j] = 0;
		primes.push_back(i);
	}
}

//solo funciona para 0 <= N <= primes[primes.size()-1]^2
bool isPrime(ll N) { 
	if (N < bs.size()) return bs[N];
	for (int i = 0; i < primes.size(); i++)
	if (N % primes[i] == 0) return false;
	return true;
}

//devuelve el vector de factores primos de N
vector<int> primeFactors(int N) {
	vector<int> factors;
	int PF_idx = 0, PF = primes[PF_idx];
	while (PF * PF <= N) {
		while (N % PF == 0) {
			N /= PF;
			factors.push_back(PF);
		}
		PF = primes[++PF_idx];
	}
	if (N != 1) factors.push_back(N); // N is prime
	return factors;
}

// Una simple variacion de la funcion anterior para solo contar el numero de factores primos
int numPF(ll N) {
	int PF_idx = 0;
	ll PF = primes[PF_idx], ans = 0;
	while (PF * PF <= N) {
		while (N % PF == 0) {
			N /= PF;
			ans++;
		}
		PF = primes[++PF_idx];
	}
	if (N != 1) ans++; // N is prime
	return ans;
}

// Devuelve el numero de divisores de n (inluyendo 1 y n) uva 11876, 294
int nod(int n) {
    int d = 1;
    for (int idx = 0, p = primes[idx]; p*p <= n; p = primes[++idx]) {
        int m = 0;
        while (n % p == 0) {
            n /= p;
            m++;
        }
        d *= m + 1;
    }
    if (n != 1) d *= 2;
    return d;
}

// devuelve la suma de los divisores de N (incluyendo N y 1)
ll sumDiv(ll N) {
    ll PF_idx = 0, PF = primes[PF_idx], sum = 1;
    while (PF * PF <= N) {
        ll p = 1;
        while (N % PF == 0) {
            N /= PF;
            p *= PF;
        }
        if (p != 1) sum *= ((p * PF) - 1) / (PF - 1);
        PF = primes[++PF_idx];
    }

    if (N != 1) sum *= N + 1;
    return sum;
}

ll EulerPhi(ll n) {
	ll idx = 0, p = primes[0], ans = n;
	while (n != 1 && (p*p <= n)) {
		if (n%p == 0) ans -= ans / p;
		while (n%p == 0) n /= p;
		p = primes[++idx];
	}
	if (n != 1) ans -= ans / n;
	return ans;
}

//Algoritmo de Euclides extendidio
//ax + by = d = gcd(a,b) Devuelve d.
ll eea(ll a, ll b, ll& x, ll& y) {
	ll xx = y = 0, yy = x = 1;
	while (b) {
		ll q = a / b, t = b; b = a%b; a = t;
		t = xx; xx = x - q*xx; x = t;
		t = yy; yy = y - q*yy; y = t;
	}
	return a;
}

//Encuentra z,M tal que z%x=a, z%y=b, unica mod M.
//Si no hay, M=-1;
ll_ll chinese(ll x, ll a, ll y, ll b) {
	ll s, t, d = eea(x, y, s, t);
	if (a%d != b%d) return ll_ll(0, -1);
	return ii(mod(s*b*x + t*a*y, x*y), x*y / d);//(z, M)
}
ll_ll chinese(const vector<ll> &x, const vector<ll> &a) {
	ll_ll ret(a[0], x[0]);
	for (int i = 1; ret.second != -1 && i<x.size(); i++)
		ret = chinese(ret.first, ret.second, x[i], a[i]);
	return ret;
}

ll fastPowMod(ll a, ll b, ll m) {
	ll aux;
	if (b == 0) return 1;
	if (b % 2 == 0) return aux = fastPowMod(a, b / 2, m), (aux*aux) % m;
	return (a*fastPowMod(a, b - 1, m)) % m;
}

//Miller Rabin: test Las Vegas de primalidad
//k=30 deberia ser suficiente casi siempre.
bool probablyPrime(ll n, int k = 35) {
	ll s = n - 1, r = 0, a, aux;
	while (s % 2 == 0) s /= 2, r++;
	while (k--) {
		a = rand() % (n - 1); a++;
		a = fastPowMod(a, s, n);
		if (a%n == 1) continue;
		for (int i = 0; i <= r; a = (a*a) % n, i++)
		if (i == r) return false; //esto es compuesto si o si.
		else if (a == n - 1) break;
	}
	return true; //Lo mas probable es que sea primo.
}

//Algoritmo Rho de factorizacion (montecarlo)
ll_ll pollardRho(ll n) {
	ll x = 2, y = 2, d = 1, a, b;
	while (d == 1) {
		x = (x*x + 1) % n;
		y = (y*y + 1) % n;
		y = (y*y + 1) % n;
		d = eea(abs(x - y), n, a, b);
	}
	return ll_ll(d, n / d);
}

#include <bits/stdc++.h>
using namespace std;

// a % b (positive)
int mod(int a, int b) {
  return ((a % b) + b) % b;
}

// greatest common divisor
int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b , a % b);
}

// least common multiple
int lcm(int a, int b) {
  return a / gcd(a, b) * b ;
}

// Bezout : d = ax + by
int bezout(int a, int b, int *x, int *y) { 
  if (a == 0) { 
    *x = 0; 
    *y = 1; 
    return b; 
  } 
  int x1, y1;
  int gcd = bezout(b%a, a, &x1, &y1); 
  *x = y1 - (b/a) * x1; 
  *y = x1; 
  return gcd; 
} 

// ax = b (mod n)
vector<int> mod_equation(int a, int b, int n) {
  int x, y;
  vector<int> solutions;
  int d = bezout(a, n, x, y);
  if (b % d == 0) {
    x = mod(x * (b / d), n);
    for (int i = 0; i < d; i++)
    solutions.push_back(mod(x + i*(n / d), n));
  }
  return solutions;
}

// modular inverse        (-1 on failure)
int mod_inverse(int a, int n) {
  int x, y;
  int d = bezout(a, n, x, y);
  if (d > 1) return - 1;
  return mod(x , n);
}

// ax + by = c        (x = y = -1 on failure)
void linear_equation(int a, int b, int c, int & x, int & y) {
  int d = gcd(a, b);
  if (c % d) x = y = -1;
  else {
    x = c / d * mod_inverse(a / d, b / d);
    y = (c - a*x) / b;
  }
}

¬\pagebreak¬

// Eratóstenes
vector<int> primes(int n) {
  vector<bool> v(n, true);
  for (int i = 0; i < n; i++) {
    if (v[i])
      for (int cont = 2; i*cont <= n; ++cont)
        v[i*cont] = false;
  }
  vector<int> prim;
  for (int i = 2; i < n; i++)
    if (v[i]) prim.push_back(i);
  return prim;
}

// Divisores
vector<int> divisors(int n, vector<int> const& prim) {
  vector<int> divis;
  int i = 0;
  while (prim[i] <= n + 1) {
    if (n % prim[i] == 0) {
      n = n / prim[i];
      divis.push_back(prim[i]);
    }
    else ++i;
  }
}

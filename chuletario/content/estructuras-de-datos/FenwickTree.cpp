#include <vector>
using namespace std;

typedef vector<int> vi;

#define LSOne(S) (S&&(-S))

struct FenwickTree {
	vi ft;
	FenwickTree(int n) {ft.assign(n + 1, 0);}
	int rsq(int b) {
		int t = 0; 
		for (; b; b -= LSOne(b))
			t += ft[b];
		return t;
	}
	int rsq(int a, int b){return rsq(b) - (a == 1 ? 0 : rsq(a - 1));}
	void update(int k, int v) {
		for (; k < ft.size(); k += LSOne(k))
			ft[k] += v;
	}
	int lower_bound(int sum) {// min pos st sum of [0 , pos ] >= sum
	// Returns n i f no sum is >= sum, or ..1 i f empty sum is .
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= s.size() && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

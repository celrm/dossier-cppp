#include <vector>
using namespace std;

typedef vector<int> vi;

// Dynamic answers to RangeMinimumQuery
class SegmentTree {
private :
	vi A, st; // A->data, st->tree (stores indices)
	int n; // length of the interval
	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }

	void build(int p, int L, int R) { // O(n)
		if (L == R)
			st[p] = L;
		else {
			build(left(p), L, (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R);
			int p1 = st[left(p)], p2 = st[right(p)];
			st[p] = (A[p1] <= A[p2]) ? p1 : p2;
		}
	}

	int rmq(int p, int L, int R, int i, int j) { // O(log n)
		// [L, R] -> interval of the node of the tree in which we are (p)
		// [i, j] -> interval of the query
		if (i > R || j < L) return -1; // totally outside
		if (L >= i && R <= j) return st[p]; // query is larger

		// if (st[p]>=i && st[p]<=j) return st[p]; better? 
		// Si es el minimo de un segmento mas largo, lo sera de uno contenido en ese

		int p1 = rmq(left(p), L, (L + R) / 2, i, j);
		int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);
		
		if (p1 == -1) return p2;
		if (p2 == -1) return p1;
		return (A[p1] <= A[p2]) ? p1 : p2;
	}

	int updatePoint(int p, int L, int R, int idx, int new_value) { // O(log n)
		if (idx < L || idx > R) return st[p]; // no change
		if (L == idx && R == idx) { // leaf
			A[idx] = new_value; // we change it here to go up changing
			return st[p];
		}
		int p1 = updatePoint(left(p), L, (L + R) / 2, idx, new_value);
		int p2 = updatePoint(right(p), (L + R) / 2 + 1, R, idx, new_value);
		return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
	}

public :
	SegmentTree(const vi & a) {
		A = a; n = (int)a.size();
		st.assign(4 * n, 0);
		build(1, 0, n - 1);
	}

	int rmq(int i, int j) {
		return rmq(1, 0, n - 1, i, j);
	}

	void updatePoint(int idx, int new_value) {
		updatePoint(1, 0, n - 1, idx, new_value);
	}
};

#define INF 1e9

// Dynamic answers to RangeSumQuery
class SegmentTree2 {
private:
	vi A, st; // A->data, st->tree
	int n; // length of the interval
	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }

	void build(int p, int L, int R) { // O(n)
		if (L == R)
			st[p] = A[L];
		else {
			build(left(p), L, (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R);
			st[p] = st[left(p)] + st[right(p)];
		}
	}

	int rsq(int p, int L, int R, int i, int j) { // O(log n)
		// [L, R] -> interval of the node of the tree in which we are (p)
		// [i, j] -> interval of the query
		if (i > R || j < L) return -INF; // totally outside
		if (L >= i && R <= j) return st[p]; // query is larger

		int p1 = rsq(left(p), L, (L + R) / 2, i, j);
		int p2 = rsq(right(p), (L + R) / 2 + 1, R, i, j);

		if (p1 == -INF) return p2;
		if (p2 == -INF) return p1;
		return p1 + p2;
	}

	// Real update! not only adding, it is modifying! (better than Fenwick)
	int updatePoint(int p, int L, int R, int idx, int new_value) { // O(log n)
		if (idx < L || idx > R) return st[p]; // no change
		if (L == idx && R == idx) { // leaf
			A[idx] = new_value; // we change it here to go up changing
			return st[p] = new_value;
		}
		int p1 = updatePoint(left(p), L, (L + R) / 2, idx, new_value);
		int p2 = updatePoint(right(p), (L + R) / 2 + 1, R, idx, new_value);
		return st[p] = p1 + p2;
	}

public:
	SegmentTree2(const vi & a) {
		A = a; n = (int)a.size();
		st.assign(4 * n, 0);
		build(1, 0, n - 1);
	}

	int rsq(int i, int j) {
		return rsq(1, 0, n - 1, i, j);
	}

	void updatePoint(int idx, int new_value) {
		updatePoint(1, 0, n - 1, idx, new_value);
	}
};
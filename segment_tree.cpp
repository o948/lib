#include <bits/stdc++.h>
using namespace std;


struct segment_tree {

	int N;
	vector<int> min;

	void recalc(int k) {
		min[k] = ::min(min[2*k+1], min[2*k+2]);
	}

	void init(int n) {
		N = 1;
		while (N < n) {
			N <<= 1;
		}
		min.assign(2*N, INT_MAX);
	}

	void build(const vector<int>& xs) {
		init(xs.size());
		build(xs, 0, 0, N-1);
	}

	void build(const vector<int>& xs, int k, int L, int R) {
		if (xs.size() <= L) {
			return;
		}
		if (L == R) {
			min[k] = xs[L];
			return;
		}
		int mid = (L+R)/2;
		build(xs, 2*k+1, L, mid);
		build(xs, 2*k+2, mid+1, R);
		recalc(k);
	}

	void put(int i, int x) {
		put(i, x, 0, 0, N-1);
	}

	void put(int i, int x, int k, int L, int R) {
		if (i < L || R < i) {
			return;
		}
		if (L == R) {
			min[k] = x;
			return;
		}
		int mid = (L+R)/2;
		put(i, x, 2*k+1, L, mid);
		put(i, x, 2*k+2, mid+1, R);
		recalc(k);
	}

	int get_min(int i, int j) {
		return get_min(i, j, 0, 0, N-1);
	}

	int get_min(int i, int j, int k, int L, int R) {
		if (j < L || R < i) {
			return INT_MAX;
		}
		if (i <= L && R <= j) {
			return min[k];
		}
		int mid = (L+R)/2;
		return ::min(
			get_min(i, j, 2*k+1, L, mid),
			get_min(i, j, 2*k+2, mid+1, R)
		);
	}
};


int main() {
	int M = 1e6;
	int N = 1e5;
	int Q = 1e5;

	vector<int> xs(N);
	for (int i = 0; i < N; i++) {
		xs[i] = rand() % M;
	}

	segment_tree tree;
	tree.build(xs);

	while (Q--) {
		switch (rand()%2) {
			case 0: {
				int x = rand() % M;
				int i = rand() % N;

				xs[i] = x;
				tree.put(i, x);

				break;
			}
			default: {
				int i = rand() % N;
				int j = rand() % N;
				if (j < i) swap(i, j);

				int min = M;
				for (int k = i; k <= j; k++) {
					min = ::min(min, xs[k]);
				}

				assert(min == tree.get_min(i, j));
				break;
			}
		}
	}
	return 0;
}


#include <bits/stdc++.h>
using namespace std;


struct segment_tree {

	int N;
	vector<int> sum;

	void recalc(int k) {
		sum[k] = sum[2*k+1] + sum[2*k+2];
	}

	void init(int n) {
		N = 1;
		while (N < n) {
			N <<= 1;
		}
		sum.resize(2*N);
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
			sum[k] = xs[L];
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
			sum[k] = x;
			return;
		}
		int mid = (L+R)/2;
		put(i, x, 2*k+1, L, mid);
		put(i, x, 2*k+2, mid+1, R);
		recalc(k);
	}

	int get_sum(int i, int j) {
		return get_sum(i, j, 0, 0, N-1);
	}

	int get_sum(int i, int j, int k, int L, int R) {
		if (j < L || R < i) {
			return 0;
		}
		if (i <= L && R <= j) {
			return sum[k];
		}
		int mid = (L+R)/2;
		return (
			get_sum(i, j, 2*k+1, L, mid) +
			get_sum(i, j, 2*k+2, mid+1, R)
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

				int sum = 0;
				for (int k = i; k <= j; k++) {
					sum += xs[k];
				}

				assert(sum == tree.get_sum(i, j));
				break;
			}
		}
	}
	return 0;
}


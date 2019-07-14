#include <bits/stdc++.h>
using namespace std;


struct segment_tree {

	int N;
	vector<int> sum;
	vector<int> add;

	int get(int k, int L, int R) {
		return sum[k] + (R-L+1)*add[k];
	}

	void recalc(int k, int L, int R) {
		int mid = (L+R)/2;
		sum[k] = (
			get(2*k+1, L, mid) +
			get(2*k+2, mid+1, R)
		);
	}

	void init(int n) {
		N = 1;
		while (N < n) {
			N <<= 1;
		}
		sum.assign(2*N, 0);
		add.assign(2*N, 0);
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
		recalc(k, L, R);
	}

	void update(int i, int j, int x) {
		update(i, j, x, 0, 0, N-1);
	}

	void update(int i, int j, int x, int k, int L, int R) {
		if (j < L || R < i) {
			return;
		}
		if (i <= L && R <= j) {
			add[k] += x;
			return;
		}
		int mid = (L+R)/2;
		update(i, j, x, 2*k+1, L, mid);
		update(i, j, x, 2*k+2, mid+1, R);
		recalc(k, L, R);
	}

	int get_sum(int i, int j) {
		return get_sum(i, j, 0, 0, N-1);
	}

	int get_sum(int i, int j, int k, int L, int R) {
		if (j < L || R < i) {
			return 0;
		}
		if (i <= L && R <= j) {
			return get(k, L, R);
		}

		if (add[k]) {
			add[2*k+1] += add[k];
			add[2*k+2] += add[k];
			add[k] = 0;
			recalc(k, L, R);
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
				int j = rand() % N;
				if (j < i) swap(i, j);

				for (int k = i; k <= j; k++) {
					xs[k] += x;
				}
				tree.update(i, j, x);

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


#include <bits/stdc++.h>
using namespace std;


struct segment_tree {

	int N;
	vector<vector<int>> xs;

	void build(const vector<int>& arr) {
		N = 1;
		while (N < arr.size()) {
			N <<= 1;
		}
		xs.resize(2*N);
		build(arr, 0, 0, N-1);
	}

	void build(const vector<int>& arr, int k, int L, int R) {
		if (arr.size() <= L) {
			return;
		}
		if (L == R) {
			xs[k] = {arr[L]};
			return;
		}

		int mid = (L+R)/2;
		build(arr, 2*k+1, L, mid);
		build(arr, 2*k+2, mid+1, R);

		xs[k].resize(xs[2*k+1].size() + xs[2*k+2].size());
		merge(
			xs[2*k+1].begin(), xs[2*k+1].end(),
			xs[2*k+2].begin(), xs[2*k+2].end(),
			xs[k].begin()
		);
	}

	int count(int i, int j, int lo, int hi) {
		return count(i, j, lo, hi, 0, 0, N-1);
	}

	int count(int i, int j, int lo, int hi, int k, int L, int R) {
		if (j < L || R < i) {
			return 0;
		}
		if (i <= L && R <= j) {
			return (
				upper_bound(xs[k].begin(), xs[k].end(), hi) -
				lower_bound(xs[k].begin(), xs[k].end(), lo)
			);
		}

		int mid = (L+R)/2;
		return (
			count(i, j, lo, hi, 2*k+1, L, mid) +
			count(i, j, lo, hi, 2*k+2, mid+1, R)
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
		int i = rand() % N;
		int j = rand() % N;
		if (j < i) swap(i, j);

		int lo = rand() % M;
		int hi = rand() % M;
		if (hi < lo) swap(lo, hi);

		int cnt = 0;
		for (int k = i; k <= j; k++) {
			cnt += (lo <= xs[k] && xs[k] <= hi);
		}

		assert(cnt == tree.count(i, j, lo, hi));
	}
	return 0;
}


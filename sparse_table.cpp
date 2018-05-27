#include <bits/stdc++.h>
using namespace std;


struct sparse_table {

	vector<vector<int>> min;

	void build(const vector<int>& xs) {
		int n = xs.size();
		int m = log_2(n);

		min.resize(m+1);
		min[0] = xs;

		for (int k = 1; k <= m; k++) {
			int len = 1<<k;
			min[k].resize(n-len+1);
			for (int i = 0; i <= n-len; i++) {
				min[k][i] = ::min(min[k-1][i], min[k-1][i + len/2]);
			}
		}
	}

	int get_min(int i, int j) {
		int k = log_2(j-i+1);
		return ::min(min[k][i], min[k][j - (1<<k) + 1]);
	}

	int log_2(int n) {
		return 31 - __builtin_clz(n);
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

	sparse_table table;
	table.build(xs);

	while (Q--) {
		int i = rand() % N;
		int j = rand() % N;
		if (j < i) swap(i, j);

		int min = INT_MAX;
		for (int k = i; k <= j; k++) {
			min = ::min(min, xs[k]);
		}

		assert(min == table.get_min(i, j));
	}
	return 0;
}


#include <bits/stdc++.h>
using namespace std;


struct binary_indexed_tree {

	int N;
	vector<int> sum;

	void init(int n) {
		N = n+1;
		sum.assign(N, 0);
	}

	void add(int i, int x) {
		for (i++; i < N; i += i&-i) {
			sum[i] += x;
		}
	}

	int get(int i) {
		int tot = 0;
		for (i++; i > 0; i -= i&-i) {
			tot += sum[i];
		}
		return tot;
	}

	int get(int i, int j) {
		return get(j) - (i > 0 ? get(i-1) : 0);
	}
};


int main() {
	int M = 1e6;
	int N = 1e5;
	int Q = 1e5;

	vector<int> xs(N);

	binary_indexed_tree tree;
	tree.init(N);

	while (Q--) {
		switch (rand()%2) {
			case 0: {
				int x = rand() % M;
				int i = rand() % N;

				xs[i] += x;
				tree.add(i, x);

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

				assert(sum == tree.get(i, j));
				break;
			}
		}
	}
	return 0;
}


#include <bits/stdc++.h>
using namespace std;


struct segment_tree {

	struct node {
		int sum;
		int left;
		int right;

		node(int sum, int left, int right)
			: sum(sum), left(left), right(right) {}
	};

	int N;
	vector<node> nodes;

	int make_node(int x, int left, int right) {
		nodes.emplace_back(x, left, right);
		return nodes.size()-1;
	}

	void recalc(int r) {
		nodes[r].sum = (
			nodes[nodes[r].left].sum +
			nodes[nodes[r].right].sum
		);
	}

	int build(const vector<int>& xs) {
		N = xs.size();
		return build(xs, 0, N-1);
	}

	int build(const vector<int>& xs, int L, int R) {
		if (L == R) {
			return make_node(xs[L], -1, -1);
		}
		int mid = (L+R)/2;
		int left = build(xs, L, mid);
		int right = build(xs, mid+1, R);
		int r = make_node(0, left, right);
		recalc(r);
		return r;
	}

	int put(int i, int x, int r=-1) {
		if (r == -1) {
			r = nodes.size()-1;
		}
		return put(i, x, r, 0, N-1);
	}

	int put(int i, int x, int r, int L, int R) {
		if (L == R) {
			return make_node(x, -1, -1);
		}
		int rr;
		int mid = (L+R)/2;
		if (i <= mid) {
			int left = put(i, x, nodes[r].left, L, mid);
			rr = make_node(0, left, nodes[r].right);
		} else {
			int right = put(i, x, nodes[r].right, mid+1, R);
			rr = make_node(0, nodes[r].left, right);
		}
		recalc(rr);
		return rr;
	}

	int get_sum(int i, int j, int r=-1) {
		if (r == -1) {
			r = nodes.size()-1;
		}
		return get_sum(i, j, r, 0, N-1);
	}

	int get_sum(int i, int j, int r, int L, int R) {
		if (j < L || R < i) {
			return 0;
		}
		if (i <= L && R <= j) {
			return nodes[r].sum;
		}
		int mid = (L+R)/2;
		return (
			get_sum(i, j, nodes[r].left, L, mid) +
			get_sum(i, j, nodes[r].right, mid+1, R)
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
	int r = tree.build(xs);

	vector<tuple<int, int, int, int>> check;

	while (Q--) {
		switch (rand()%2) {
			case 0: {
				int x = rand() % M;
				int i = rand() % N;

				xs[i] = x;
				r = tree.put(i, x);

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
				check.emplace_back(i, j, r, sum);

				break;
			}
		}
	}

	for (auto it : check) {
		int i, j, r, sum;
		tie(i, j, r, sum) = it;
		assert(sum == tree.get_sum(i, j, r));
	}

	return 0;
}


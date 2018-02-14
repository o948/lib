#include <bits/stdc++.h>
using namespace std;


struct bst {

	struct node {
		int x;
		int size;
		int left;
		int right;

		node(int x, int left, int right)
			: x(x), left(left), right(right) {}
	};

	int root = -1;
	vector<node> vs;

	int new_node(int x, int left, int right) {
		int r = vs.size();
		vs.emplace_back(x, left, right);
		recalc(r);
		return r;
	}

	void recalc(int r) {
		if (r == -1) return;
		vs[r].size = 1;
		if (vs[r].left != -1) {
			vs[r].size += vs[vs[r].left].size;
		}
		if (vs[r].right != -1) {
			vs[r].size += vs[vs[r].right].size;
		}
	}

	void split(int x, int r, int& a, int& b) {
		if (r == -1) return;
		if (x <= vs[r].x) {
			int mid = -1;
			split(x, vs[r].left, a, mid);
			vs[r].left = mid;
			b = r;
		} else {
			int mid = -1;
			split(x, vs[r].right, mid, b);
			vs[r].right = mid;
			a = r;
		}
		recalc(a);
		recalc(b);
	}

	int join(int a, int b) {
		if (a == -1) return b;
		if (b == -1) return a;
		if (rand() % (vs[a].size + vs[b].size) < vs[a].size) {
			vs[a].right = join(vs[a].right, b);
			recalc(a);
			return a;
		} else {
			vs[b].left = join(a, vs[b].left);
			recalc(b);
			return b;
		}
	}

	int size() {
		return root != -1 ? vs[root].size : 0;
	}

	void add(int x) {
		root = add(x, root);
	}

	int add(int x, int r) {
		if (r == -1) {
			return new_node(x, -1, -1);
		}
		if (rand() % (vs[r].size + 1) == 0) {
			int a = -1;
			int b = -1;
			split(x, r, a, b);
			return new_node(x, a, b);
		}
		if (x < vs[r].x) {
			int rr = add(x, vs[r].left);
			vs[r].left = rr;
		} else {
			int rr = add(x, vs[r].right);
			vs[r].right = rr;
		}
		recalc(r);
		return r;
	}

	void del(int x) {
		root = del(x, root);
	}

	int del(int x, int r) {
		if (r == -1) return -1;
		if (x == vs[r].x) {
			return join(vs[r].left, vs[r].right);
		}
		if (x < vs[r].x) {
			vs[r].left = del(x, vs[r].left);
		} else {
			vs[r].right = del(x, vs[r].right);
		}
		recalc(r);
		return r;
	}

	bool has(int x) {
		return has(x, root);
	}

	bool has(int x, int r) {
		if (r == -1) return false;
		if (x < vs[r].x) return has(x, vs[r].left);
		if (x > vs[r].x) return has(x, vs[r].right);
		return true;
	}

	int kth(int k) {
		assert(1 <= k && k <= size());
		return kth(k, root);
	}

	int kth(int k, int r) {
		int lsize = vs[r].left != -1 ? vs[vs[r].left].size : 0;
		if (k <= lsize) {
			return kth(k, vs[r].left);
		} else {
			k -= lsize;
		}
		if (k == 1) {
			return vs[r].x;
		} else {
			k--;
		}
		return kth(k, vs[r].right);
	}
};


int main() {
	int M = 1e3;
	int N = 1e5;
	int Q = 1e5;

	set<int> xs;
	bst tree;

	while (Q--) {
		switch (rand()%2) {
			case 0: {
				int x = rand() % M;
				if (xs.count(x)) {
					xs.erase(x);
					assert(tree.has(x));
					tree.del(x);
				} else {
					xs.insert(x);
					assert(!tree.has(x));
					tree.add(x);
				}
				break;
			}
			default: {
				int k = 0;
				for (auto x : xs) {
					k++;
					assert(x == tree.kth(k));
				}
			}
		}
		assert(xs.size() == tree.size());
	}
	return 0;
}


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

	int left_size(int r) {
		return vs[r].left != -1 ? vs[vs[r].left].size : 0;
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

	void split(int k, int r, int& a, int& b) {
		if (r == -1) return;
		if (k <= left_size(r)) {
			int mid = -1;
			split(k, vs[r].left, a, mid);
			vs[r].left = mid;
			b = r;
		} else {
			int mid = -1;
			split(k-left_size(r)-1, vs[r].right, mid, b);
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

	void insert(int i, int x) {
		assert(0 <= i && i <= size());
		int a = -1;
		int b = -1;
		split(i, root, a, b);
		root = join(join(a, new_node(x, -1, -1)), b);
	}

	void remove(int i) {
		assert(0 <= i && i < size());
		if (i == 0) {
			int _ = -1;
			int r = -1;
			split(1, root, _, r);
			root = r;
		} else {
			int a = -1;
			int rest = -1;
			split(i, root, a, rest);
			int _ = -1;
			int b = -1;
			split(1, rest, _, b);
			root = join(a, b);
		}
	}

	int get(int i) {
		assert(0 <= i && i < size());
		return get(i, root);
	}

	int get(int i, int r) {
		if (i+1 <= left_size(r)) {
			return get(i, vs[r].left);
		} else {
			i -= left_size(r);
		}
		if (i == 0) {
			return vs[r].x;
		} else {
			i--;
		}
		return get(i, vs[r].right);
	}

	vector<int> get_all() {
		vector<int> xs;
		get_all(root, xs);
		return xs;
	}

	void get_all(int r, vector<int>& xs) {
		if (r == -1) return;
		get_all(vs[r].left, xs);
		xs.push_back(vs[r].x);
		get_all(vs[r].right, xs);
	}
};


int main() {
	int M = 1e6;
	int Q = 1e5;

	vector<int> xs;
	bst tree;

	while (Q--) {
		switch (rand()%2) {
			case 0: {
				int i = rand() % (xs.size()+1);
				int x = rand() % M;

				xs.insert(xs.begin()+i, x);
				tree.insert(i, x);

				break;
			}
			default: {
				if (!xs.empty()) {
					int i = rand() % xs.size();

					xs.erase(xs.begin()+i);
					tree.remove(i);
				}
				break;
			}
		}
		assert(tree.size() == xs.size());

		vector<int> ys = tree.get_all();
		assert(ys.size() == xs.size());

		for (int i = 0; i < ys.size(); i++) {
			assert(ys[i] == tree.get(i));
			assert(ys[i] == xs[i]);
		}
	}
	return 0;
}


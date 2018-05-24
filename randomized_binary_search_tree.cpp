#include <bits/stdc++.h>
using namespace std;


struct binary_search_tree {

	struct node {
		const int x;

		int size = 1;
		node* left = nullptr;
		node* right = nullptr;

		node(int x) : x(x) {}
	};

	node* root = nullptr;

	void recalc(node* r) {
		r->size = 1;
		if (r->left != nullptr) {
			r->size += r->left->size;
		}
		if (r->right != nullptr) {
			r->size += r->right->size;
		}
	}

	void split(node* r, int x, node*& lt, node*& ge) {
		if (r == nullptr) return;
		if (x <= r->x) {
			node* tmp = nullptr;
			split(r->left, x, lt, tmp);
			ge = r;
			ge->left = tmp;
			recalc(ge);
		} else {
			node* tmp = nullptr;
			split(r->right, x, tmp, ge);
			lt = r;
			lt->right = tmp;
			recalc(lt);
		}
	}

	void split(node* r, int x, node*& lt, node*& eq, node*& gt) {
		node* tmp = nullptr;
		split(root, x, lt, tmp);
		split(tmp, x+1, eq, gt);
	}

	node* join(node* r1, node* r2) {
		if (r1 == nullptr) return r2;
		if (r2 == nullptr) return r1;

		int k = rand() % (r1->size + r2->size);
		if (k < r1->size) {
			r1->right = join(r1->right, r2);
			recalc(r1);
			return r1;
		} else {
			r2->left = join(r1, r2->left);
			recalc(r2);
			return r2;
		}
	}

	int size() {
		return root != nullptr ? root->size : 0;
	}

	void add(int x) {
		node* lt = nullptr;
		node* eq = nullptr;
		node* gt = nullptr;
		split(root, x, lt, eq, gt);

		if (eq == nullptr) {
			eq = new node(x);
		}

		root = join(join(lt, eq), gt);
	}

	void del(int x) {
		node* lt = nullptr;
		node* eq = nullptr;
		node* gt = nullptr;
		split(root, x, lt, eq, gt);

		if (eq != nullptr) {
			delete eq;
			eq = nullptr;
		}

		root = join(join(lt, eq), gt);
	}

	bool has(int x) {
		return has(root, x);
	}

	bool has(node* r, int x) {
		if (r == nullptr) return false;
		if (x < r->x) return has(r->left, x);
		if (x > r->x) return has(r->right, x);
		return true;
	}

	int kth(int k) {
		assert(1 <= k && k <= size());
		return kth(root, k);
	}

	int kth(node* r, int k) {
		int lsize = r->left != nullptr ? r->left->size : 0;
		if (k <= lsize) {
			return kth(r->left, k);
		} else {
			k -= lsize;
		}
		if (k == 1) {
			return r->x;
		} else {
			k--;
		}
		return kth(r->right, k);
	}
};


int main() {
	int M = 1e3;
	int N = 1e5;
	int Q = 1e5;

	set<int> xs;
	binary_search_tree tree;

	while (Q--) {
		switch (rand()%2) {
			case 0: {
				int x = rand() % M;
				if (xs.count(x)) {
					xs.erase(x);
					assert(tree.has(x));
					tree.del(x);
					assert(!tree.has(x));
				} else {
					xs.insert(x);
					assert(!tree.has(x));
					tree.add(x);
					assert(tree.has(x));
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


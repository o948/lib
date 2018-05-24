#include <bits/stdc++.h>
using namespace std;


struct rope {

	struct node {
		const int x;

		int size = 1;
		node* left = nullptr;
		node* right = nullptr;

		node(int x) : x(x) {}
	};

	node* root = nullptr;

	int left_size(node* r) {
		return r->left != nullptr ? r->left->size : 0;
	}

	void recalc(node* r) {
		r->size = 1;
		if (r->left != nullptr) {
			r->size += r->left->size;
		}
		if (r->right != nullptr) {
			r->size += r->right->size;
		}
	}

	void split(node* r, int k, node*& r1, node*& r2) {
		if (r == nullptr) return;
		if (k <= left_size(r)) {
			node* tmp = nullptr;
			split(r->left, k, r1, tmp);
			r2 = r;
			r2->left = tmp;
			recalc(r2);
		} else {
			node* tmp = nullptr;
			split(r->right, k-left_size(r)-1, tmp, r2);
			r1 = r;
			r1->right = tmp;
			recalc(r1);
		}
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

	void insert(int i, int x) {
		assert(0 <= i && i <= size());
		node* r1 = nullptr;
		node* r2 = nullptr;
		split(root, i, r1, r2);
		root = join(join(r1, new node(x)), r2);
	}

	void remove(int i) {
		assert(0 <= i && i < size());
		if (i == 0) {
			node* _ = nullptr;
			node* r = nullptr;
			split(root, 1, _, r);
			root = r;
		} else {
			node* r1 = nullptr;
			node* tmp = nullptr;
			split(root, i, r1, tmp);
			node* _ = nullptr;
			node* r2 = nullptr;
			split(tmp, 1, _, r2);
			root = join(r1, r2);
		}
	}

	int get(int i) {
		assert(0 <= i && i < size());
		return get(root, i);
	}

	int get(node* r, int i) {
		if (i+1 <= left_size(r)) {
			return get(r->left, i);
		} else {
			i -= left_size(r);
		}
		if (i == 0) {
			return r->x;
		} else {
			i--;
		}
		return get(r->right, i);
	}

	vector<int> get_all() {
		vector<int> xs;
		get_all(root, xs);
		return xs;
	}

	void get_all(node* r, vector<int>& xs) {
		if (r == nullptr) return;
		get_all(r->left, xs);
		xs.push_back(r->x);
		get_all(r->right, xs);
	}
};


int main() {
	int M = 1e6;
	int Q = 1e5;

	vector<int> xs;
	rope r;

	while (Q--) {
		switch (rand()%2) {
			case 0: {
				int i = rand() % (xs.size()+1);
				int x = rand() % M;

				xs.insert(xs.begin()+i, x);
				r.insert(i, x);

				break;
			}
			default: {
				if (!xs.empty()) {
					int i = rand() % xs.size();

					xs.erase(xs.begin()+i);
					r.remove(i);
				}
				break;
			}
		}
		assert(r.size() == xs.size());

		vector<int> ys = r.get_all();
		assert(ys.size() == xs.size());

		for (int i = 0; i < ys.size(); i++) {
			assert(ys[i] == r.get(i));
			assert(ys[i] == xs[i]);
		}
	}
	return 0;
}


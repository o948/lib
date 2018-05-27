#include <bits/stdc++.h>
using namespace std;


struct union_find {
	vector<int> r;
	vector<int> p;

	void build(int n) {
		r.assign(n, 0);
		p.assign(n, 0);
		iota(p.begin(), p.end(), 0);
	}

	void unify(int u, int v) {
		u = find(u);
		v = find(v);
		if (r[u] == r[v]) {
			r[v]++;
		}
		if (r[u] < r[v]) {
			p[u] = v;
		} else {
			p[v] = u;
		}
	}

	int find(int u) {
		if (p[u] == u) return u;
		p[u] = find(p[u]);
		return p[u];
	}
};


int main() {
	int N = 1e5;
	int Q = 1e5;

	vector<int> ids(N);
	iota(ids.begin(), ids.end(), 0);

	union_find r;
	r.build(N);

	while (Q--) {
		int u = rand() % N;
		int v = rand() % N;
		switch (rand()%2) {
			case 0: {
				int x = ids[u];
				int y = ids[v];
				for (int i = 0; i < N; i++) {
					if (ids[i] == x) {
						ids[i] = y;
					}
				}
				r.unify(u, v);

				assert(r.find(u) == r.find(v));
				break;
			}
			default: {
				assert((r.find(u) == r.find(v)) == (ids[u] == ids[v]));
				break;
			}
		}
	}
	return 0;
}


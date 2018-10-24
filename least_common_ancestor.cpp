#include <bits/stdc++.h>
using namespace std;


struct least_common_ancestor {

	int K;
	vector<int> h;
	vector<vector<int>> up;

	void build(int n, const vector<int> g[]) {
		K = log_2(n);

		h.resize(n);
		dfs1(g, 0, -1);

		up.resize(K+1, vector<int>(n));
		dfs2(g, 0, -1);
	}

	void dfs1(const vector<int> g[], int u, int p) {
		for (int v : g[u]) {
			if (v == p) continue;
			h[v] = h[u] + 1;
			dfs1(g, v, u);
		}
	}

	void dfs2(const vector<int> g[], int u, int p) {
		if (p != -1) {
			up[0][u] = p;
			for (int i = 1; i <= K; i++) {
				up[i][u] = up[i-1][ up[i-1][u] ];
			}
		}
		for (int v : g[u]) {
			if (v == p) continue;
			dfs2(g, v, u);
		}
	}

	int get(int u, int v) {
		if (h[u] != h[v]) {
			if (h[u] < h[v]) {
				swap(u, v);
			}
			int k = h[u] - h[v];
			for (int i = 0; i <= K; i++) {
				if (k & 1<<i) {
					u = up[i][u];
				}
			}
		}
		if (u == v) {
			return u;
		}
		for (int i = K; i >= 0; i--) {
			if (up[i][u] != up[i][v]) {
				u = up[i][u];
				v = up[i][v];
			}
		}
		return up[0][u];
	}

	int dist(int u, int v) {
		return h[u] + h[v] - 2*h[get(u, v)];
	}

	int log_2(int n) {
		return 31 - __builtin_clz(n);
	}
};


void flatten(vector<int> g[], int u, int p, vector<int>& arr, vector<int>& idx) {
	idx[u] = arr.size();
	arr.push_back(u);
	for (int v : g[u]) {
		if (v == p) continue;
		flatten(g, v, u, arr, idx);
		arr.push_back(u);
	}
}

int main() {
	int N = 1e5;
	int Q = 1e5;

	vector<int> g[N];
	for (int u = 1; u < N; u++) {
		int v = rand() % u;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<int> arr;
	vector<int> idx(N);
	flatten(g, 0, -1, arr, idx);

	least_common_ancestor lca;
	lca.build(N, g);

	while (Q--) {
		int u = rand() % N;
		int v = rand() % N;

		int i = idx[u];
		int j = idx[v];
		if (j < i) swap(i, j);

		int w = 1e9;
		while (i <= j) {
			w = min(w, arr[i]);
			i++;
		}

		assert(w == lca.get(u, v));
	}
	return 0;
}


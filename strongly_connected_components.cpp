#include <bits/stdc++.h>
using namespace std;


void scc_dfs1(int u, const vector<int> g[], vector<bool>& was, vector<int>& done, int& t) {
	was[u] = true;
	for (int v : g[u]) {
		if (was[v]) continue;
		scc_dfs1(v, g, was, done, t);
	}
	done[u] = t++;
}

void scc_dfs2(int u, const vector<vector<int>>& g, vector<bool>& was, vector<int>& ans) {
	was[u] = true;
	for (int v : g[u]) {
		if (was[v]) continue;
		scc_dfs2(v, g, was, ans);
	}
	ans.push_back(u);
}

vector<vector<int>> scc(int n, const vector<int> g[]) {
	vector<int> ord;
	{
		vector<bool> was(n);
		vector<int> done(n);
		int t = 0;

		for (int u = 0; u < n; u++) {
			if (was[u]) continue;
			scc_dfs1(u, g, was, done, t);
		}

		ord.resize(n);
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&done](int i, int j) {
			return done[i] > done[j];
		});
	}

	vector<vector<int>> gg(n);
	for (int u = 0; u < n; u++) {
		for (int v : g[u]) {
			gg[v].push_back(u);
		}
	}

	vector<vector<int>> ans;
	{
		vector<bool> was(n);
		for (int u : ord) {
			if (was[u]) continue;
			ans.emplace_back();
			scc_dfs2(u, gg, was, ans.back());
		}
	}
	return ans;
}


int main() {
	int n;
	vector<int> g[100];

	n = 8;
	g[0] = {1};
	g[1] = {2, 4, 5};
	g[2] = {3, 6};
	g[3] = {2, 7};
	g[4] = {0, 5};
	g[5] = {6};
	g[6] = {5, 7};
	g[7] = {7};

	vector<set<int>> ans;
	ans.push_back({0, 1, 4});
	ans.push_back({2, 3});
	ans.push_back({5, 6});
	ans.push_back({7});

	auto out = scc(n, g);

	assert(out.size() == ans.size());
	for (int i = 0; i < out.size(); i++) {
		assert(out[i].size() == ans[i].size());
		for (int u : out[i]) {
			assert(ans[i].count(u));
		}
	}

	return 0;
}


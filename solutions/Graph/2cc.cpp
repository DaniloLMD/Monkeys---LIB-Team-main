#include <bits/stdc++.h>
using namespace std;

// template

typedef long long ll;

const int N = 200100;

int cs = 1;  // Time of entry in u
int qt_comp;    // Number of strongly connected components
int id[N];
int low[N],rot[N];  // Lowest ID in u's subtree in DFS tree
vector<int> adj[N];
vector<int> comp[N], stk;
void dfs(int u, int p = -1) {
	id[u] = low[u] = cs++;
	stk.pb(u);
    // careful with multiple edges
    int did = 0;

	for (int v : adj[u]) {
		if (v == p && !did) {
			did = 1;
			continue;
		}
		if (!id[v]) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], id[v]);
		}
	}

	if (low[u] == id[u]) {
		while (stk.back() != u) {
            rot[stk.back()] = qt_comp;
			comp[qt_comp].pb(stk.back());
			stk.pop_back();
		}
        rot[stk.back()] = qt_comp;
		comp[qt_comp++].pb(stk.back());
		stk.pop_back();
	}
}

int main() {
	int n, m;
	cin >> n >> m;
    rep(i, 0, m) {
		int x, y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

    rep(u, 0, n)
		if (!id[u])
            dfs(u);
	

	cout << qt_comp << '\n';
    rep(i, 0, qt_comp) {
		cout << comp[i].size() << ' ';
		for (int u : comp[i]) { cout << u << ' '; }
		cout << '\n';
	}
}
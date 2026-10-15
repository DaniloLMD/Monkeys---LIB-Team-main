#include <bits/stdc++.h>
using namespace std;

//template

const int N = 200100;

int cs = 1;
int id[N],low[N];
int vis[N],ap[N];
vector<int> adj[N];

void dfs(int u, int p) {
	vis[u] = 1;
	id[u] = low[u] = cs++;

	int sz = 0;
	for (int v : adj[u]) {
		if (v == p) 
            continue;

		if (!vis[v]) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			sz++;

			// Check if the current u is an articualation point
			if (low[v] >= id[u] && p != u)
                ap[u] = 1;
		} else {
			low[u] = min(low[u], id[v]);
		}
	}
	if (p == u && sz > 1)
        ap[u] = 1;
}

int main() {
	int n,m;
    cin >> n >> m;
    rep(i, 1, n+1){
        adj[i].clear();
        ap[i] = vis[i] = 0;
    }
    cs = 1;
    rep(i, 0, m)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1, 1);

    int rs = 0;
    rep(i, 1, n+1)
        rs += ap[i];
    cout << rs << '\n';
}
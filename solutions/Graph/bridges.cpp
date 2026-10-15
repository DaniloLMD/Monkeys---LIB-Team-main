#include <bits/stdc++.h>
using namespace std;

//template

const int N = 200100;

int cs = 1;
int id[N],low[N];
int vis[N];
vector<int> adj[N];
vector<pii> bridges;
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

			// Check if the current u-v is an bridge
			if (low[v] > id[u])
                bridges.eb(u,v);
		} else {
			low[u] = min(low[u], id[v]);
		}
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
	int n,m;
    cin >> n >> m;
    rep(i, 1, n+1){
        adj[i].clear();
        vis[i] = 0;
    }
    bridges.clear();
    cs = 1;
    rep(i, 0, m)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1, 1);

    cout << bridges.size() << "\n";
    for(auto [u,v]:bridges)
        cout << u << ' ' << v << '\n';
}
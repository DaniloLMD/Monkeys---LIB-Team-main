#include <bits/stdc++.h>
using namespace std;
//template
const int N = 200100; // tem que ser 2x o numero de vertices do grafo
const int K = 20;
int cs = 1, qt_comp = 0;
int id[N],low[N], rot[N];
int vis[N],ap[N];
vector<int> adj[N], tree[N];
vector<int> comp[N], stk;
void dfs0(int u, int p) {
	vis[u] = 1;
	id[u] = low[u] = cs++;
    stk.pb(u);
	for (int v : adj[u]) {
		if (v == p) 
            continue;

		if (!vis[v]) {
			dfs0(v, u);
			low[u] = min(low[u], low[v]);
			// Check if the current u is an articualation point
			if (low[v] >= id[u] && p != u)
            {
                ap[u] = (id[u] > 1 || id[v] > 2);
                comp[qt_comp].pb(u);
                while (comp[qt_comp].back() != v) {
                    comp[qt_comp].pb(stk.back());
                    stk.pop_back();
                }
                qt_comp++;
            }
		} else {
			low[u] = min(low[u], id[v]);
		}
	}
}
int n_tree;
// return the size of the tree
int build_block(int n)
{
    dfs0(1, -1);
	// Build the block-cut tree
    int node_id = 1;
    rep(i, 1, n+1)
        if (ap[i])
            rot[i] = node_id++;
    
    rep(j, 0, qt_comp) {
			int node = node_id++;
			for (int u : comp[j])
				if (!ap[u]) {
					rot[u] = node;
				} else {
					tree[node].pb(rot[u]);
					tree[rot[u]].pb(node);
				}
		}
	return node_id-1;
}

int up[N][K], in[N], out[N],tmp = 0;;
void dfs(int u, int p)
{
    in[u] = tmp++;
    up[u][0] = p;
    rep(j, 1, K) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (auto v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    out[u] = tmp-1;
}
bool is_ancestor(int u, int v)
{
    return (in[u] <= in[v] && out[v] <= out[u]);
}
int calc_lca(int u, int v)
{
    if(is_ancestor(u,v))
        return u;

    if(is_ancestor(v,u))
        return v;
    rep(j, (int)K, 0)
    {
        if(!is_ancestor(up[u][j],v))
            u = up[u][j];
    }
    return up[u][0];
}
int main() {
	int n, m, q;
	cin >> n >> m >> q;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	n_tree = build_block(n);

	// Check whether the node z is on path (x, y)
	auto on_path = [&](int x, int y, int z) {
		int lca = calc_lca(x, y);
		int lca1 = calc_lca(x, z);
		int lca2 = calc_lca(y, z);

		if (lca == z || (lca1 == lca && lca2 == z) ||
		    (lca2 == lca && lca1 == z)) {
			return true;
		}
		return false;
	};

	dfs(1, 1);

	for (int i = 0; i < q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		// The path does not exist in two cases:
		// 1) a == c or b == c
		// 2) c is a cutpoint and it lies on path between a and b in block-cut
		// tree
		if (a == c || b == c ||
		    (ap[c] && on_path(rot[a], rot[b], rot[c]))) {
			cout << "NO\n";
		} else {
			cout << "YES" << '\n';
		}
	}
}
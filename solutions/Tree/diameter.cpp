const int N = 200100;

vector<int> adj[N];

pair<int, int> dfs_diameter(int u, int p, int dep)
{
    pair<int, int> best;
    best = {dep, u};
    for(int v : adj[u])
        if(v != p)
            best = max(best, dfs_diameter(v, u, dep+1));
    return best;
}


void test()
{
    int n;
    cin >> n;
    for(int i = 0, u, v, t; i < n-1; i++)
    {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int at = dfs_diameter(1, 1, 1).second;
    cout << dfs_diameter(at, at, 1).first << '\n';
}
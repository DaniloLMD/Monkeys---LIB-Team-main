#include<bits/stdc++.h>
using namespace std;

map<vector<int>, int> hasher;
int hashify(vector<int> x) {
    sort(all(x));
    if(!hasher[x]) {
        hasher[x] = hasher.size();
    }
    return hasher[x];
}
class Tree
{
    public:
    vector<vector<int>> adj;
    vector<int> sub, pai;
    int r[2], hs[2], n, bt = 0;
    Tree(int x): n(x)
    {
        adj.resize(n+1);
        sub.resize(n+1, 0);
        pai.resize(n+1);
    }
    void add_edge(int u, int v)
    {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int dfs(int u, int p = -1)
    {
        vector<int>  at;
        for(int v:adj[u])
        {
            if(v == p)
                continue;
            at.pb(dfs(v, u));
        }
        return hashify(at);
    }
    void dfs_sub(int u, int p = -1)
    {
        pai[u] = p;
        sub[u] = 1;
        for(int v:adj[u])
        {
            if(v == p)
                continue;
            dfs_sub(v, u);
            sub[u]+=sub[v];
        }
    }
    int find_centroid(int u, int p = -1)
    {
        // cout << u << '\n';
        for(int v:adj[u])
        {
            if(v == p)
                continue;
            if(2*sub[v] > n)
                return find_centroid(v, u);
        }
        return u;
    }
    void build()
    {
        bt = 1;
        dfs_sub(1);
        r[1] = r[0] = find_centroid(1);
        for(int v:adj[r[0]])
        {
            if(v == pai[r[0]])
            {
                if(2*(n-sub[r[0]]) >= n)
                    r[1] = v;
            }else
            {
                if(2*sub[v] >= n)
                    r[1] = v;
            }
        }
        hs[0] = dfs(r[0]);
        hs[1] = dfs(r[1]);
    }
    

    bool isIsomorphic(Tree t2)
    {
        if(!bt)
            build();
        if(!t2.bt)
            t2.build();
        rep(i, 0, 2)
        {
            rep(j, 0, 2)
            {
                if(hs[i] == t2.hs[j]){
                    // cout << r[i] << ' ' << t2.r[j] << "<<<\n";
                    return true;
                }
            }
        }
        return false;
    }
};







void test()
{
    int n;
    cin >> n;
    Tree t1(n), t2(n);
    rep(i, 0, n-1)
    {
        int u, v;
        cin >> u >> v;
        t1.add_edge(u, v);
    }
    rep(i, 0, n-1)
    {
        int u, v;
        cin >> u >> v;
        t2.add_edge(u, v);
    }

    if(t1.isIsomorphic(t2))
        cout << "YES\n";
    else
        cout << "NO\n";
    // hasher.clear();
}


int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while(t--)
        test();
    return 0;
}
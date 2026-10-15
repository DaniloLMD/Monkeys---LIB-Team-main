#include <bits/stdc++.h>
using namespace std;
//template

const int N = 200100;

vector<int> adj[N],tree[N],r_adj[N],bucket[N];
int sdom[N],par[N],dom[N],dsu[N],rot[N];
int in[N],rev[N],cs = 1;
//1-Based directed graph input
int findx(int u,int x=0)
{
    if(u==dsu[u])return x?-1:u;
    int v = findx(dsu[u],x+1);
    if(v<0)return u;
    if(sdom[rot[dsu[u]]]<sdom[rot[u]])
        rot[u] = rot[dsu[u]];
    dsu[u] = v;
    return x?v:rot[u];
}
void merge(int u,int v){ //Add an edge u-->v
    dsu[v]=u;   
}
void dfs0(int u)
{
    rev[cs]=u;
    in[u] = rot[cs] = sdom[cs] = dsu[cs] = cs;
    cs++;
    for(int v:adj[u])
    {
        if(!in[v]){
            dfs0(v);
            par[in[v]]=in[u];
        }
        r_adj[in[v]].pb(in[u]);
    }
}

void build_dominator_tree(int n, int s)
{
    dfs0(s);
    rep(u, n+1, 1)
    {
        for(int v:r_adj[u])
            sdom[u] = min(sdom[u], sdom[findx(v)]);
        if(u > 1)
            bucket[sdom[u]].pb(u);

        for(int v:bucket[u]){
            int w = findx(v);
            if(sdom[v] == sdom[w])
                dom[v] = sdom[v];
            else
                dom[v] = w;
        }
        if(u > 1)
            merge(par[u],u);
    }
    rep(i, 2, n+1)
    {
        if(dom[i]!=sdom[i])
            dom[i]=dom[dom[i]];
        tree[rev[i]].pb(rev[dom[i]]);
        tree[rev[dom[i]]].pb(rev[i]);
    }
}

int pai[N];

void dfs(int u, int p)
{
    for(int v:tree[u])
    {
        if(v == p)
            continue;
        pai[v] = u;
        dfs(v,u);
    }
}

void test(){
    int n, m;
    cin >> n >> m;
    while(m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
    }
    build_dominator_tree(n,1);
    dfs(1,1);
    int at = n;
    vector<int> resp;
    while(at)
    {
        resp.pb(at);
        at = pai[at];
    }
    cout << resp.size() << '\n';
    sort(all(resp));
    for(int x:resp)
        cout << x << ' ';
    cout << '\n';
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while(t--) test();
    return 0;
}
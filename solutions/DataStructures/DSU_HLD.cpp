#include <bits/stdc++.h>
using namespace std;
#define sq(x) (1ll*(x)*(x))
#define lef(x) ((x)<<1)
#define rig(x) (lef(x)|1)
#define get_bit(x,i) ((x)&(1ll<<(i)))
 
using ll = long long;
using ld = long double;
 
// Indexado em 1
// Alterar o que cada grupo tem
struct DSU{
    // o que cada grupo carrega de informacao
    struct gp{
        int tam = 0;
        vector<int> vtx; // vertices
        void init(int x){
            tam = 1, vtx.push_back(x);
        }
        void clear(){
            tam = 0, vtx.clear();
        }
    };
    
    int n;
    vector<int> repre;
    vector<gp> smol;

    // se t = 0, aloca sem init
    DSU (int nn,int t = 1) : n(nn), repre(nn+1), smol(nn+1){
        if(t){
            for(int i=1; i<=n; i++){
                repre[i]=i;
                smol[i].init(i);
            }
        }
    }
    void init(int nn){
        n = nn;
        for(int i=1; i<=n; i++){
            repre[i] = i;
            smol[i].init(i);
        }
    }


    int rep(int u){
        return repre[u] = (repre[u] == u ? u : rep(repre[u]));
    }
    gp & smoll(int u){
        return smol[rep(u)];
    }

    // unir u e v
    void unite(int u,int v,int t = 0){
        u = rep(u), v = rep(v);
        if(u == v) return;
        auto &x=smol[u];
        auto &y=smol[v];
        if(y.tam > x.tam){
            unite(v,u,t);
            return;
        }
        // da merge nos smols
        merge(x,y,t);
        repre[v]=u;
    }
    // fazer o merge de 2 grupos
    void merge(gp &x, gp &y,int t){
        // faz o merge se precisar
        for(auto v : y.vtx) x.vtx.push_back(v);
        x.tam += y.tam;
        y.clear();
    }
};
 
const int MAX = 2e5 + 10;

vector<int> graph[MAX]; int tam[MAX];
int c[MAX],cnt[MAX], res[MAX], qt = 0;
DSU dsu(MAX,0); 

void dfs_tam(int u,int ant){
    tam[u] = 1;
    for(auto& v : graph[u]){
        if(v == ant) continue;
        dfs_tam(v,u);
        tam[u] += tam[v];
        if(graph[u][0] == ant || tam[v] > tam[graph[u][0]]) 
            swap(v,graph[u][0]);
    }
}
 
void solve(int u, int ant, bool keep = false){
    int hv = (graph[u].empty() || graph[u][0] == ant ? -1 : graph[u][0]);
    for(auto v : graph[u]){
        if(v == ant || v == hv) continue;
        solve(v,u);
        dsu.unite(v,u);
    }
    if(hv != -1) solve(hv,u,true);
    for(auto x : dsu.smoll(u).vtx){
        if(!cnt[c[x]]) qt++;
        cnt[c[x]]++;
    }
    res[u] = qt;
    if(hv != -1) dsu.unite(u,hv);
    if(!keep) for(auto x : dsu.smoll(u).vtx){
        cnt[c[x]]--;
        qt = 0;
    }
}
 
void test(){
    int n;
    cin >> n;
    for(int i=1; i<=n; i++) cin >> c[i];
    dsu.init(n);
    
    vector<int> ord;
    for(int i=1; i<=n; i++) ord.push_back(c[i]);
    sort(ord.begin(),ord.end()); 
    ord.erase(unique(ord.begin(),ord.end()),ord.end());
    for(int i=1; i<=n; i++) 
        c[i] = lower_bound(ord.begin(),ord.end(),c[i]) - ord.begin();
 
    for(int i=1; i<n; i++){
        int x,y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs_tam(1,1);
    solve(1,1);
    for(int i=1; i<=n; i++) cout << res[i] << ' ';
    cout << '\n';
}
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t_=1;
    // cin >> t_;
    while(t_--) test();
    return 0;
}
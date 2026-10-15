#include <bits/stdc++.h>
using namespace std;
#define get_bit(x,i) ((x)&(1ll<<(i)))
#define el '\n'
using ll = long long int; using ull = uint64_t; using ld = long double;
template<class T> using vc = vector<T>; template<class T> using vvc = vector<vc<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node{
    int val = 0;
    bool off = false;int l = 0,r = 0;
    node(){}
    friend void merge(node &x,node &y,node &at){
        if(x.off) return void(at = y);
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)
        at.val = x.val + y.val;
    }
};
struct upd{
    int val;
    upd(int vall = 0) : val(vall){}
    // aplica upd
    friend void apply(node &at,upd &x){
        at.val += x.val;
    }
};
template <class node, class upd>
struct perSeg{
    #define lef(x) seg[x].l
    #define rig(x) seg[x].r
    perSeg(int nn = 0,vc<node> &v = {}) : n(nn),seg(1),rev(1,0){
        assert(nn == v.size());
        build(0,0,n-1,v);
    }
    int n; vc<node> seg;
    vc<int> rev; // raiz da revisao
    node ret,aux;
    int get_rev(){return int(rev.size())-1;}
    void build(int u,int tl,int tr,vc<node>& v){
        if(tl == tr) return void(seg[u] = v[tl]);
        int tmid = tl + tr; tmid >>= 1;
        lef(u) = seg.size(); seg.emplace_back();
        rig(u) = seg.size(); seg.emplace_back();
        build(lef(u),tl,tmid,v),build(rig(u),tmid+1,tr,v);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void update(int u,int nu,int tl,int tr,int id,upd &x){
        if(tl == tr) return apply(seg[nu],x);
        int tmid = tl + tr; tmid >>= 1;
        lef(nu) = lef(u), rig(nu) = rig(u);
        if(id <= tmid){
            lef(nu) = seg.size(); seg.emplace_back(seg[lef(u)]);
            update(lef(u),lef(nu),tl,tmid,id,x);
        }else{
            rig(nu) = seg.size(); seg.emplace_back(seg[rig(u)]);
            update(rig(u),rig(nu),tmid+1,tr,id,x);
        }
        merge(seg[lef(nu)],seg[rig(nu)],seg[nu]);
    }
    void update(int id,upd x,int r){
        rev.push_back(seg.size()); seg.emplace_back(seg[rev[r]]);
        update(rev[r],rev.back(),0,n-1,id,x);
    }
    int query(int u,int v,int z,int zz,int k,int tl,int tr){
        if(tl == tr) return tl;
        int tmid = tl + tr; tmid >>= 1;
        int x = seg[lef(u)].val + seg[lef(v)].val - seg[lef(z)].val - seg[lef(zz)].val;
        if(x >= k) return query(lef(u),lef(v),lef(z),lef(zz),k,tl,tmid);
        return query(rig(u),rig(v),rig(z),rig(zz),k-x,tmid+1,tr);
    }
    int query(int u,int v,int z,int zz,int k){
        return query(rev[u],rev[v],rev[z],rev[zz],k,0,n-1);
    }
    #undef lef
    #undef rig
};

const int MAX = 1e5 + 10;

vc<int> graph[MAX];
int a[MAX];
int tam[MAX],p[MAX],hd[MAX],tin[MAX],timer = 0;

void dfs1(int u,int ant){
    tam[u] = 1;
    for(auto& v : graph[u]){
        if(v == ant) swap(v,graph[u].back());
        if(v != ant){
            dfs1(v,u);
            tam[u] += tam[v];
            if(graph[u][0] == ant || tam[graph[u][0]] < tam[v]) swap(v,graph[u][0]);
        }
    }
    if(graph[u].back() == ant) graph[u].pop_back();
}
void dfs(int u,int ant,perSeg<node,upd>& seg){
    p[u] = ant, hd[u] = (u == ant ? u : hd[u]), tin[u] = ++timer;
    seg.update(a[u],upd(1),(ant == u ? 0 : tin[ant]));
    for(auto v : graph[u]){
        hd[v] = (v == graph[u][0] ? hd[u] : v);
        dfs(v,u,seg);
    }
}
bool lca(int u,int v){return tin[u] <= tin[v] && tin[v]+tam[v]-1 <= tin[u]+tam[u]-1;}
int get_lca(int u,int v){
    int aux = u;
    for(; !lca(u,v); u = p[hd[u]]);
    for(; !lca(v,aux); v = p[hd[v]]);
    return lca(u,v) ? v : u;
}

void test(){
    int n,q; cin >> n >> q;
    for(int i=0; i<n; i++) cin >> a[i];
    vc<int> ord; for(int i=0; i<n; i++) ord.push_back(a[i]);
    sort(ord.begin(),ord.end()); ord.erase(unique(ord.begin(),ord.end()),ord.end());
    for(int i=0; i<n; i++) a[i] = lower_bound(ord.begin(),ord.end(),a[i]) - ord.begin();
    for(int i=1; i<n; i++){
        int x,y; cin >> x >> y;
        x--,y--;
        graph[x].push_back(y), graph[y].push_back(x);
    }
    vc<node> init(n);
    perSeg<node,upd> seg(n,init);
    dfs1(0,0); dfs(0,0,seg);
    for(int i=0; i<q; i++){
        int x,y,k; cin >> x >> y >> k;
        x--,y--;
        int z = get_lca(x,y);
        // cout << get_lca(x,y) << endl;
        cout << ord[seg.query(tin[x],tin[y],tin[z],z ? tin[p[z]] : 0,k)] << el;
    }
}

int main (){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
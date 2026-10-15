#include <bits/stdc++.h>
using namespace std;
 
using ll = long long int;
 
/*
    Indexado de 1
*/
struct Centroid{
    vector<vector<int>> & graph; // referencia da arvore original
    int n; // qtd de vertices 
    vector<int> tam; // tam da subarvore
    vector<bool> vis; // visitado para construir o centroide
    vector<int> p; // o pai de cada cara no centroide
    int r; // raiz do centroide
    vector<ll> cnt;
    int k;
    ll qt = 0;
 
    Centroid(int nn, vector<vector<int>> & ggraph, int kk) : n(nn), graph(ggraph), tam(nn+1),vis(nn+1,false),
    p(nn+1), cnt(nn+1,0), k(kk){
        // cnt.resize(nn+1);
        r = build(1);
    }
 
    // constroi o centroid decomposition
    int build(int u){
        set_tam(u,u);
        u = find_centroid(u);
        vis[u]=1;
 
        // se tiver que fazer algum calculo durante o centroid decomposition
        calc(u);
 
        p[u]=u;
        for(auto v: graph[u]){
            if(vis[v]) continue;
            int x=build(v);
            p[x]=u;
        }    
        return u;
    }
 
    void set_tam(int u,int ant){
        tam[u]=1;
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            set_tam(v,u);
            tam[u]+=tam[v];
        }
    }
    int find_centroid(int u){
        while(1){
            int flag=1;
            for(auto v: graph[u]){
                if(vis[v]) continue;
                if(tam[v]*2 > tam[u]){
                    tam[u]-=tam[v];
                    tam[v]+=tam[u];
                    u=v;
                    flag=0;
                    break;
                }
            }
            if(flag) break;
        }
        return u;
    }
 
    void calc(int u,int ant, int sz, int d = 1){
        if(d > k) return;
        qt += cnt[k-d];
        // faz algum tipo de calculo
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            calc(v,u,sz,d+1);
        }
    }
    void update(int u,int ant, int d = 1){
        if(d > k) return; // clutch
        cnt[d]++;
        // faz algum tipo de update
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            update(v,u,d+1);
        }
    }
    void reset(int u,int ant, int d = 0){
        if(d > k) return; // clutch
        cnt[d]--;
        // reseta as coisas que eu fiz nos updates
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            reset(v,u,d+1);
        }
    }
    void calc(int u){
        if(tam[u] < k) return; // clutch
        cnt[0]++;
        for(auto v: graph[u]){
            if(vis[v]) continue;
            calc(v,u,tam[u]); // calcular essa subarvore, passo esse tamanho pra dar uma otimizada no limite dessa subarvore
            update(v,u); // atualizar essa subarvore
        }
        // limpa as coisas
        reset(u,u);
    }
};
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k;
    cin >> n >> k;
    vector<vector<int>> graph(n+1);
    for(int i=1; i<n; i++){
        int x,y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    Centroid c(n,graph,k);
    cout << c.qt << '\n';
    return 0;
}
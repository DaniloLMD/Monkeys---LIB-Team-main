#include <bits/stdc++.h>
using namespace std;

#define lef(x) ((x)<<1)
#define rig(x) (lef(x)|1)

const int MAX = 20;

// include MCMF
struct info{
    int x,y,v;
};

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<char>> a(n,vector<char>(m));
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin >> a[i][j];
    
    vector<info> lin,col,W;
    for(int i=0; i<k; i++){
        char c;
        int x,y,v;
        cin >> c >> x >> y >> v;
        x--,y--;
        if(c == 'V') col.push_back({x,y,v});
        else lin.push_back({x,y,v});
    }
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) if(a[i][j] != '0') 
        W.push_back({i,j,a[i][j]-'1'});
    int qt_W = W.size(), qt_lin = lin.size(), qt_col = col.size();
    
    // computar as restricoes de cada celula branca
    vector<vector<pair<int,int>> who(n,vector<pair<int,int>>(m));
    for(int j=0; j<qt_lin; j++){
        auto [x,y,v] = lin[j];
        for(int i=1; y+i < m && a[x][y+i] != '0'; i++) 
            lin[j].v--,who[x][y+i].first = j;
    }
    for(int j=0; j<qt_col; j++){
        auto [x,y,v] = col[j];
        for(int i=1; x+i < n && a[x+i][y] != '0'; i++) 
            col[j].v--,who[x+i][y].second = j;
    } 
    
    // construir a rede
    int sz = qt_lin+qt_col+2*qt_W+10, src = sz-1, snk = sz-2;
    MCMF mcmf(sz);
    for(int i=0; i<qt_lin; i++) mcmf.add_edge(src,i,lin[i].v,0);
    for(int i=0; i<qt_col; i++) mcmf.add_edge(qt_lin+i,snk,col[i].v,0);
    for(int i=0; i<qt_W; i++){
        auto [x,y,v] = W[i];
        int iat = qt_lin+qt_col+lef(i), oat = qt_lin+qt_col+rig(i);
        int l = who[x][y].first, c = qt_lin+who[x][y].second;
        mcmf.add_edge(l,iat,8,0);
        mcmf.add_edge(iat,oat,v,-1);
        mcmf.add_edge(iat,oat,8-v,1);
        mcmf.add_edge(oat,c,8,0);
    }
    
    // o custo das restricoes deve ser igual ao fluxo e a resposta vai ser a soma dos W's - custo_minimo
    auto ret = mcmf.mcmf(src,snk);
    int s1 = 0, s2 = 0, s3 = 0;
    for(int i=0; i<qt_lin; i++) s1 += lin[i].v; 
    for(int i=0; i<qt_col; i++) s2 += col[i].v; 
    for(int i=0; i<qt_W; i++) s3 += W[i].v;
    if(s1 != s2 || ret.first != s1) cout << "IMPOSSIBLE\n";
    else cout << s3 + ret.second << '\n';
    
    return 0;
}
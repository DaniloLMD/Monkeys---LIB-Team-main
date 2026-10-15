#include <bits/stdc++.h>
using namespace std;

const int MAX = (int) 1e3 + 10;

char a[MAX][MAX];
int visi[MAX<<1];
int b[MAX][MAX];
vector<pair<int,int>> graph[MAX<<1];
int vis[MAX*MAX], d[MAX*MAX];
vector<int> ord;
int n,m;

void get_ord(int u){
    while(!graph[u].empty()){
        auto [v,id] = graph[u].back();
        graph[u].pop_back();
        if(vis[id]) continue;
        vis[id] = 1;
        get_ord(v);
    }
    ord.push_back(u);
}

void dfs(int u){
    visi[u] = 1;
    for(auto [v,id] : graph[u]){
        if(visi[v]) continue;
        int lin = (u < n ? u : v);
        int col = (u < n ? v - n : u - n);
        dfs(v);
    }
}

void test(){
    cin >> n >> m;
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin >> a[i][j];

    int timer = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == '.'){
                graph[i].push_back(make_pair(j+n,timer)); 
                graph[j+n].push_back(make_pair(i,timer++)); 
                d[i]++, d[j+n]++;
            }
        }
    }
    
    int init = -1, dst = -1;
    for(int i=0; i<n+m; i++){
        if(d[i]&1){
            if(init == -1) init = i; 
            else if(dst == -1) dst = i; 
            else{
                cout << "*\n"; 
                return;
            }
        }
    }
    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == '.' && visi[i] == 0){
                cnt++;
                dfs(i);
            }
            if(a[i][j] == '.' && visi[j+n] == 0){
                cnt++;
                dfs(j+n);
            }
        }
    }
    if(cnt > 1){
        cout << "*\n";
        return;
    }

    if(init == -1){
        for(int i=0; i<n+m; i++) if(!graph[i].empty()) init = i;
    }
    if(init != -1) get_ord(init);
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) b[i][j] = 0;

    // for(int i=0; i<ord.size(); i++) cout << ord[i] << ' ';
    // cout << '\n';

    for(int i=1; i<ord.size(); i++){
        int lin = (ord[i-1] < n ? ord[i-1] : ord[i]);
        int col = (ord[i-1] < n ? ord[i]-n : ord[i-1]-n);
        b[lin][col] = i;   
    }
    
    for(int i=0; i < n; i++){
        for(int j=0; j<m; j++) cout << b[i][j] << ' ';
        cout << '\n';
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    while(ttt_--) test();
    return 0;
}
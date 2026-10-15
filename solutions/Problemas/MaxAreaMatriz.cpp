#include <bits/stdc++.h>
using namespace std;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> mat(n,vector<int>(m)),dist(n,vector<int>(m));
    vector<int> acima(n),abaixo(n);
    // a celula eh valida se mat[i][j] == 1
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin >> mat[i][j];
    // calcular dist(i,j)
    for(int i=n-1; i>=0; i--){
        for(int j=m-1; j>=0; j--){
            if(mat[i][j] == 0) dist[i][j] = 0;
            else dist[i][j] = dist[i][j+1] + 1;
        }
    }
    // maior area possivel
    int ans = 0;
    // calcular acima(i,j) e abaixo(i,j)
    vector<pair<int,int>> st;
    for(int j=0; j<m; j++){
        for(int i=0; i<n; i++){
            while(!st.empty() && st.back().first >= dist[i][j])
                st.pop_back();
            if(st.empty()) acima[i] = 0;
            else acima[i] = st.back().second+1;
            st.emplace_back(dist[i][j],i);
        }
        while(!st.empty()) st.pop_back();

        for(int i=n-1; i>=0; i--){
            while(!st.empty() && st.back().first >= dist[i][j])
                st.pop_back();
            if(st.empty()) abaixo[i][j] = n-1;
            else abaixo[i] = st.back().second-1;
            st.emplace_back(dist[i][j],i);
        }
        while(!st.empty()) st.pop_back();

        for(int i=0; i<n; i++) ans = max(ans, dist[i][j] (abaixo[i] - acima[i] + 1));
    }
    cout << ans << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int MAX = (int) 1e2+10;
const int MAX_S= (int) 1e5+10;
 
int h[MAX],s[MAX],qtd[MAX];
int dp[MAX_S];
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,x;
    cin >> n >> x;
    for(int i=0; i<n; i++){
        cin >> h[i];
    }
    for(int i=0; i<n; i++){
        cin >> s[i];
    }
    for(int i=0; i<n; i++){
        cin >> qtd[i];
    }
    vector<pair<int,int>> a;
    for(int i=0; i<n; i++){
        int aux=1;
        while(qtd[i] > aux){
            a.push_back({h[i]*aux,s[i]*aux});
            qtd[i]-=aux;
            aux+=aux;
        }
        if(qtd[i]) a.push_back({h[i]*qtd[i],s[i]*qtd[i]});
        qtd[i]=0;
    }
    int m=a.size();
    memset(dp,-1,sizeof(dp));
    dp[0]=0;
    int ans=0;
    for(int i=0; i<m; i++){
        for(int j=x; j>=a[i].first; j--){
            if(dp[j-a[i].first] == -1) continue;
            dp[j]=max(dp[j],dp[j-a[i].first]+a[i].second);
            ans=max(ans,dp[j]);
        }
    }
    cout << ans << '\n';
    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_x
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = (int) 1e3+10;
const int MAX_S= (int) 1e4+10;

struct opa{
    int w,s;
    ll v;
};

pair<int,opa> lista[MAX];
ll dp[MAX_S<<1];

bool compara(pair<int,opa> &a, pair<int,opa> &b){
    if(a.first < b.first) return true;
    if(a.first == b.first && a.second.s < b.second.s) return true;
    if(a.first == b.first && a.second.s == b.second.s && a.second.w < b.second.w) return true;
    return false;
}

// basicamente ordena por peso+solidez
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> lista[i].second.w >> lista[i].second.s >> lista[i].second.v;
        lista[i].first=lista[i].second.w+lista[i].second.s;
    }
    sort(lista,lista+n, compara);
    ll ans=0;
    for(int i=0 ;i<(MAX_S<<1); i++) dp[i]=-1;
    dp[0]=0;
    for(int i=0; i<n; i++){
        for(int j=lista[i].second.s; j>=0; j--){
            if(dp[j] == -1) continue;
            dp[j+lista[i].second.w]=max(dp[j]+lista[i].second.v,dp[j+lista[i].second.w]);
            ans=max(ans,dp[j+lista[i].second.w]);
        }
    }
    cout << ans << '\n';
    return 0;
}
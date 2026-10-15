#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> X(n);
    for(int i=0; i<n; i++) cin >> X[i];
    vector<vector<ll>> d(2);
    for(int i=1; i<n; i++) d[i&1].push_back(X[i]-X[i-1]);
    for(int j=0; j<2; j++) sort(d[j].begin(),d[j].end());
    for(int j=0; j<2; j++) reverse(d[j].begin(),d[j].end());
    ll ans = X[0], acum = X[0];
    for(int i=1; i<n; i++){
        if(!d[i&1].empty()) acum += d[i&1].back(), d[i&1].pop_back();
        ans += acum;
    }
    cout << ans << '\n';
    return 0;
}
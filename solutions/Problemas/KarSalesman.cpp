#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    ll maior=0, s=0;
    for(int i=0; i<n; i++) maior=max(maior,a[i]), s+=a[i];
    cout << max(maior,s/x+(s%x != 0)) << '\n';
    return 0;
}
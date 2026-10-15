#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = (int) 510;
const ll mod = 1e9+7;
 
ll dp[MAX*MAX];
ll pref[MAX*MAX];
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k;
    cin >> n >> k;
    dp[0]=1;
    pref[0]=1;
    pref[1]=1;
    for(int i=2; i<=n; i++){
        for(int j=k; j>0; j--){
            dp[j]=pref[j];
        }
        for(int j=1; j<=i; j++){
            pref[j]=(pref[j-1]+dp[j])%mod;
        }
        for(int j=i+1; j<=k; j++) pref[j]=(pref[j-1]+dp[j]-dp[j-i-1]+mod)%mod;
    }
    cout << dp[k] << '\n';
    return 0;
}
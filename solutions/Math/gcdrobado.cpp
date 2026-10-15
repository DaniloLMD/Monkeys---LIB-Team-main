//UVALive-6582
#include <bits/stdc++.h>
using namespace std;

const int N=100010;
typedef long long ll;
const ll mod=998244353LL;

map<ll, ll> sub_gcd[N];
ll a[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin>> q;
    while(q--)
    {
        int n;
        cin>>n;
        for (int i = 0; i < n; ++i)
        {
            cin>>a[i];
            sub_gcd[i].clear();
        }
        sub_gcd[0][a[0]] = 1;
        ll ans=0;
        for(int i = 1; i < n; i++)
        {
            sub_gcd[i][a[i]] = 1;
            for(auto it: sub_gcd[i - 1])
            {
                ll new_gcd = __gcd(it.first, a[i]);
                sub_gcd[i][new_gcd] = max(sub_gcd[i][new_gcd], it.second + 1);  
            }
        }
        for (int i = 0; i < n; ++i)
            for(auto it: sub_gcd[i])
                ans=max(ans,it.first*it.second);
        cout<<ans<<'\n';
    }
    return 0;
}  
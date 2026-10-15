#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200100;
const int M = 60;

const ll bmod = 1000'000'007LL;
const ll mod = 2;

ll a[N][M];

ll fexp(ll x, ll b, ll mod)
{
    ll rs = 1;
    while(b)
    {
        if(b&1)
            rs = rs * x % mod;
        x = x * x % mod;
        b >>= 1;
    }
    return rs;
}
ll inv(ll x)
{
    return 1;
}
int n;
ll compute_rank() {

    int rank = 0;
    vector<bool> row_selected(n, false);
    for (int i = 0; i < M; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            if (!row_selected[j] && a[j][i] > 0)
                break;
        }
        // cout << i << endl;
        if (j != n) {
            ++rank;
            row_selected[j] = true;
            for (int p = i + 1; p < M; ++p)
                a[j][p] = a[j][p] * inv(a[j][i]) % mod;
            for (int k = 0; k < n; ++k) {
                if (k != j && a[k][i] > 0) {
                    for (int p = i + 1; p < M; ++p)
                        a[k][p] = (a[k][p] - a[j][p] * a[k][i] % mod + mod) % mod;
                }
            }
        }
    }
    // error(rank);
    return fexp(mod,n-rank,bmod);
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for(int i = 0; i < n; i++){
        ll x;
        cin >> x;
        for(int j = 0; j < M; j++)
        {
            if(x & (1LL<<j))
                a[i][j] = 1;
        }

    }
    ll at = compute_rank();
    // error(at);
    cout << (fexp(mod, n, bmod) - at + bmod) %bmod  << '\n';
    
    return 0;
}

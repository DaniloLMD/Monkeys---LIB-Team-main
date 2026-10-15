#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = (int) 1e5+10;

// CHT template

ll a[MAX],b[MAX];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    /*
        A DP eh DP[i] = min_{j < i}(DP[j] + b[j] * a[i]), dai so usamos o CHT, nesse caso, os
    slopes estao ordenados, entao podemos usar o CHT estatico, mas tbm da pra usar o dinamico.
    */
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    for(int i=0; i<n; i++) cin >> a[i];
    for(int i=0; i<n; i++) cin >> b[i];
    CHT cht;
    cht.add(b[0],0);
    ll tmp = 0;
    for(int i=1; i<n; i++){
        tmp = cht.query(a[i]);
        cht.add(b[i],tmp);
    }
    cout << tmp << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

ll PA(ll x){return (1+x)*x/2ll;}
bool check(int x, int d, int h){
    x++;
    int r1 = d%x, r2 = x - r1;
    return r2 * PA(d/x) + r1 * PA(d/x+1) < x-1+h;
}

int32_t main (){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int h,d;
    cin >> h >> d;
    int l = 0, r = d+10;
    int mid, ans = r;
    while(l <= r){
        mid = l + r;
        mid >>= 1;
        if(check(mid,d,h)) {
            ans = mid;
            r = mid-1;
        }else l = mid+1;
    }
    cout << d + ans << '\n';
    return 0;
}
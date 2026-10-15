#include <bits/stdc++.h>
using namespace std;

#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

using ll = long long;

vector<ll> fat, ifat, primes;

ll gcd(ll a, ll b, ll &x, ll &y) {
    if(a == 0){
        x = 0;
        y = 1;
        return b;
    }
    ll x0, y0;
    ll g = gcd(b%a, a, x0, y0);
    y = x0;
    x = y0-x0*(b/a);
    return g;
}

ll fexp(ll a, ll b, ll p) {
    a %= p;
    ll rs = 1;
    while(b>0){
        if(1ll&b) rs = rs*a%p;
        a = a*a%p;
        b>>=1ll;
    }
    return rs;
}

void _set(int p) {
    fat.assign(p, 0);
    ifat.assign(p, 0);

    fat[0]=fat[1]=1;
    ifat[0]=ifat[1]=1;
    for(ll i=2; i<p; i++){
        fat[i]=(fat[i-1]*i)%p;
        ifat[i]=fexp(fat[i],p-2, p);
    }
}

void factorize(int m) {
    primes.clear();
    for(int i=2; i<= 50; i++) {
        if(m%i==0){
            primes.pb(i);
            while(m%i==0) m/=i;
        }
    }
}

ll Lucas(ll n, ll r, ll p) {
    if(r<0 || r>n) return 0;
    if(r==0 || r==n) return 1;

    if(n>=p) return (Lucas(n/p,r/p,p)*Lucas(n%p,r%p,p))%p;
    return ((fat[n]*ifat[r])%p*ifat[n-r])%p;
}

pair<ll,ll> crt(ll a, ll n, ll b, ll m) {
    if(a<0) a += n;
    if(a>=n) a %= n;
    if(b<0) b += m;
    if(b >= m) b %= m;
    ll x1, x2;
    ll d = gcd(n, m, x1, x2);
    ll lcm = n*m/d;
    if((a-b)%d != 0){
        return mp(-1, lcm);
    }

    ll x = (a+(n*x1)*(__int128_t)((b-a)/d))%lcm;
    if(x<0) x+=lcm;
    return mp(x, lcm);
}

void test() {
    ll n, r, m;
    cin >> n >> r >> m;
    factorize(m);
    ll rs=0, M = 1;
    for(int i=0; i<primes.size(); i++) {
        _set(primes[i]);
        tie(rs, M) = crt(rs, M, Lucas(n, r, primes[i]), primes[i]);
    }
    cout<<rs<<"\n";
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);

    int t = 1;
    cin >> t;

    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
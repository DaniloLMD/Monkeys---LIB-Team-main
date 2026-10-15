long long mult(long long a, long long b, long long mod) {
    return (__int128)a * b % mod;
}

long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod;
}

long long rho(long long n, long long x0=2, long long c=1) {
    long long x = x0;
    long long y = x0;
    long long g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = gcd(abs(x - y), n);
    }
    return g;
}


void solve(ll p){//usando pollard para achar todos os primos de um numero qualquer, usando crivo para os menores que um x e rho para os maiores.
    if(MillerRabin(p)) st.insert(p);
    else{
        if(p < N * N){
            rep(i,0,pl.size()){
                while(p % pl[i] == 0){
                    st.insert(pl[i]);
                    p /= pl[i];
                }
            }
            if(p > 1) st.insert(p);
        }
        else{
            ll px;
            px = rho(p);
            solve(px);
            solve(p/px);
        }
    }
}
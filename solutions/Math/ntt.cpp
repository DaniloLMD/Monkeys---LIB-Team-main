// retornar vector nao eh tao paia
using C = complex<double>;
using vd = vector<double>;
using vl = vector<long long int>;
using vi = vector<int>;
const ll mod = (119 << 23) + 1, root = 62; // = 998244353
int modpow(int b, int e) {
    int ans = 1;
    for (; e; b = 1ll * b * b % mod, e >>= 1)
        if (e & 1) ans = 1ll * ans * b % mod;
    return ans;
}
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
void ntt(vi &a) {
    static vi rev;
    int n = a.size(), S = __builtin_ctz(max(n,(int)rev.size())/n);
    static vi rt(2, 1);
    // o k nao reseta
    for (static int k = 2, s = 2; k < n; k <<= 1, s++) {
        rt.resize(n);
        ll z[] = {1, modpow(root, mod >> s)};
        for(int i = k; i < (k << 1); i++) rt[i] = 1ll * rt[i >> 1] * z[i & 1] % mod;
    }
    if(int(rev.size()) < n){
        rev.resize(n);
        for(int i = 0; i < n; i++) rev[i] = (rev[i>>1] | ((i&1)*n)) >> 1;
    }
    for(int i = 0; i < n; i++) if (i < (rev[i] >> S)) swap(a[i], a[rev[i] >> S]);
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += (k << 1)) for(int j = 0; j < k; j++) {
            int z = 1ll * rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
            a[i + j + k] = ai - z + (z > ai ? mod : 0);
            ai += (ai + z >= mod ? z - mod : z);
        }
}
vi conv_ntt(const vi &a, const vi &b) {
    if (a.empty() || b.empty()) return {};
    int s = a.size() + b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    vi L(a), R(b), out(n);
    int inv = modpow(n, mod - 2);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    for(int i = 0; i < n; i++)
        out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
}
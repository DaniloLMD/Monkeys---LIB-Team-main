// String Hash - Polynomial rolling hash

const int N = 200100;
const uint64_t p=33, mod=1000000007, p2=73, mod2=1000000009;
uint64_t ppow[N], ppow2[N];

void build()
{
    ppow[0] = 1;
    ppow2[0] = 1;
    for (int i = 1; i < N; i++) {
        ppow[i] = (ppow[i-1] * p) % mod;
        ppow2[i] = (ppow2[i-1] * p2) % mod2;
    }
}
struct Hash {
    vector<pair<uint64_t, uint64_t>> h;
 
    Hash () {}
 
    void init(string &s) {
        h.resize(s.size()+2);
        h[0] = {5389ULL, 5389ULL};
        for (size_t i = 0; i < s.size(); i++) {
            int code = s[i];
            h[i+1].first = (h[i].first * p + code) % mod;
            h[i+1].second = (h[i].second * p2 + code) % mod2;
        }
    }
 
    pair<uint64_t, uint64_t> get_hash(int i, int j) {
        pair<uint64_t, uint64_t> r;
        r.first = (h[j+1].first - (h[i].first * ppow[j-i+1]) % mod + mod) % mod;
        r.second = (h[j+1].second - (h[i].second * ppow2[j-i+1]) % mod2 + mod2) % mod2;
        return r;
    }
};

uint64_t fastExp(uint64_t a, uint64_t p, uint64_t mod) {
	return p == 0 ? 1 : ((fastExp((a * a) % mod, p / 2, mod) % mod) * (p & 1 ? a%mod : 1)) % mod;
}

pair<uint64_t, uint64_t> repeatHash(pair<uint64_t, uint64_t> r, int size, int qtd){
    uint64_t q = ppow[size], q2 = ppow2[size];
    uint64_t num = fastExp(q, qtd, mod) - 1, num2 = fastExp(q2, qtd, mod2) - 1;
    uint64_t den = fastExp((q  - 1) , mod - 2, mod), den2 = fastExp((q2  - 1), mod2 - 2, mod2);
    return mp((num * den % mod) * r.ft % mod, (num2 * den2 % mod2) * r.sd % mod2);
}

pair<uint64_t, uint64_t> getQtdCharsInACiclicSubstring(int l, int r, int qtd, Hash &hat){
    int size = r - l + 1;
    if (qtd <= size){
        return hat.get_hash(l, l+qtd-1);
    }
    pair<uint64_t, uint64_t> h = hat.get_hash(l, r);
    int integerPart = qtd / size;
    int rest = qtd - size * integerPart;
    pair<uint64_t, uint64_t> repeatedPart = repeatHash(h, size, integerPart, hat);
    pair<uint64_t, uint64_t> restPart = (rest == 0 ? mp((uint64_t)0, (uint64_t)0) : hat.get_hash(l, l+rest-1));
    return mp(
        (restPart.ft + repeatedPart.ft * ppow[rest] % mod) % mod,
        (restPart.sd + repeatedPart.sd * ppow2[rest] % mod2) % mod2
    );
}

*/
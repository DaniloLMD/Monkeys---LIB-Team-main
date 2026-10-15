const int N = 2010;
const uint64_t p[4] = {33, 73, 37, 93}, mod[2] = {1000000007, 1000000009};
uint64_t ppow[4][N];

void build()
{
    for (int j = 0; j < 4; j++){
        ppow[j][0] = 1;        
        for (int i = 1; i < N; i++) {
            ppow[j][i] = (ppow[j][i-1] * p[j]) % mod[j>>1];
        }
    }
}
struct Hash {
    int n, m;
    vector<vector<pair<uint64_t, uint64_t>>>h;
 
    Hash () {}
 
    void init(vector<string> &word2d) {
        n = word2d.size();
        m = word2d[0].size();
        h.resize(n+1, vector(m+1, mp((uint64_t)0,(uint64_t)0)));

        pair<uint64_t, uint64_t> sv;    
        for (int i = 1; i <= n; i++) {
            sv = {0, 0};
            for (int j = 1; j <= m; j++){
                int code = word2d[i-1][j-1];
                sv = {(sv.ft * p[0] + code)%mod[0],
                      (sv.sd * p[2] + code)%mod[1]};
                h[i][j] = {(h[i-1][j].ft * p[1])%mod[0] + sv.ft,
                           (h[i-1][j].sd * p[3])%mod[1] + sv.sd};
                if (h[i][j].ft >= mod[0]) h[i][j].ft -= mod[0];
                if (h[i][j].sd >= mod[1]) h[i][j].sd -= mod[1];
            }
        }
    }
    
    pair<uint64_t, uint64_t> get_hash(int i, int j, int height, int width) {
        int i2 = i + height, j2 = j + width;
        pair<uint64_t, uint64_t> r = {
            (h[i2][j2].ft + mod[0] + mod[0]
                - (h[i][j2].ft * ppow[1][i2-i])%mod[0] 
                - (h[i2][j].ft * ppow[0][j2-j])%mod[0]
                + ((ppow[1][i2-i] * ppow[0][j2-j])%mod[0] * h[i][j].ft)%mod[0]
            )%mod[0],
            (h[i2][j2].sd + mod[1] + mod[1]
                - (h[i][j2].sd * ppow[3][i2-i])%mod[1] 
                - (h[i2][j].sd * ppow[2][j2-j])%mod[1]
                + ((ppow[3][i2-i] * ppow[2][j2-j])%mod[1] * h[i][j].sd)%mod[1]
            )%mod[1]
        };
        return r;
    }
};

Hash h1, h2;
vector<string> ss1, ss2;

void test()
{
    int n,m,n2,m2;
    string s;
    cin >> n >> m;
    rep(i, 0, n){
        cin >> s;
        ss1.pb(s);
    }
    cin >> n2 >> m2;
    rep(i, 0, n2){
        cin >> s;
        ss2.pb(s);
    }
    build();
    h1.init(ss1);
    h2.init(ss2);

    auto target = h1.get_hash(0, 0, n, m);
    for(int i = 0; i < n2 - n + 1; i++){
        for(int j = 0; j < m2 - m + 1; j++){
            if (target == h2.get_hash(i, j, n, m)){
                cout << "MATCH " << i << " " << j << "\n";
            }
        }
    }
}
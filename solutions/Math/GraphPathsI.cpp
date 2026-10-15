
typedef long long ll;
const int N = 100;
const ll mod = 1000000007LL;
ll mat[N][N], resp[N][N], aux[N][N];
void mult(ll a[N][N], ll b[N][N])
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            aux[i][j] = 0;
            for(int k = 0; k < N; k++)
                aux[i][j] = (aux[i][j] + a[i][k] * b[k][j] % mod) % mod; 
        }
 
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            a[i][j] = aux[i][j];
}
void show(ll a[N][N], int n)
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cout << a[i][j] << ' ';
        cout << '\n';
    }
}
void fasexp(ll b)
{
    for(int i = 0; i < N; i++){
        resp[i][i] = 1;
    }
    while(b)
    {
        if(b&1)
            mult(resp,mat);
        mult(mat,mat);
        b >>= 1;
    }
}
int dp[N];
 
int main()
{
    int n, m;
    ll k;
    cin >> n >> m >> k;
    while(m --)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;   
        mat[u][v]++;
    }
    fasexp(k);
    // show(resp, n);
    cout << resp[0][n-1] << '\n';
    return 0;
}
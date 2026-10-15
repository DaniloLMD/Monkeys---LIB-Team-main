
typedef long long ll;
const int N = 100;
ll mat[N][N], resp[N][N], aux[N][N];
void mult(ll a[N][N], ll b[N][N])
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            aux[i][j] = -1;
            for(int k = 0; k < N; k++){
                if(a[i][k] == -1 || b[k][j] == -1)
                    continue;
                if(aux[i][j] == -1)
                    aux[i][j] = a[i][k] + b[k][j];
                aux[i][j] = min(aux[i][j] , a[i][k] + b[k][j]); 
            }
        }
 
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            a[i][j] = aux[i][j];
}
void fasexp(ll b)
{
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
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    ll k;
    cin >> n >> m >> k;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            mat[i][j] = -1;
            resp[i][j] = -1;
        }
        resp[i][i] = 0;
    }
    while(m --)
    {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;   
        if(mat[u][v] == -1)
            mat[u][v] = c;
        mat[u][v] = min(mat[u][v], (ll)c);
    }
    fasexp(k);
    cout << resp[0][n-1] << '\n';
    return 0;
}

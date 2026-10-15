// Example of sqrt decomposition
const int N = 400100;
const int K = 500;

int ans[K][N/K], bmi[K][N/K], bmx[K][N/K];
int pre[N/K],lazy[N/K], ami[N/K], amx[N/K];
int a[N], b[N];

int calc(int ini,int k)
{
    ini%=K;
    k%=K;
    k -= ini;
    if(k<0)
        k+=K;
    return k;
}

void updt(int id)
{
    int j = id*K;
    int mi = a[j];
    pre[id] = 0;
    amx[id] = a[j];
    while(j/K == id)
    {
        pre[id] = max(pre[id], a[j] - mi);
        mi = min(mi, a[j]);
        ami[id] = mi;
        amx[id] = max(amx[id], a[j]);
        j++;
    }
}

void push(int id)
{
    // cout << id << ' ' << lazy[id] << '\n';
    if(lazy[id] == -1)
        return;
    int ini = id*K;
    rep(i, 0, K)
    {
        a[ini+i] = b[lazy[id]+i];
    }
    lazy[id] = -1;
}

void build(int n)
{
    int mi;
    rep(i, 0, K)
    {
        rep(j, i, n)
        {
            if((j-i)%K == 0)
            {
                mi = b[j];
                ans[i][(j-i)/K] = 0;
                bmx[i][(j-i)/K] = b[j];
            }
            ans[i][(j-i)/K] = max(ans[i][(j-i)/K], b[j] - mi);
            mi = min(mi, b[j]);
            bmi[i][(j-i)/K] = mi;
            bmx[i][(j-i)/K] = max(bmx[i][(j-i)/K], b[j]);
        }
    }
    rep(j, 0, n)
    {
        if((j)%K == 0)
        {
            mi = a[j];
            pre[(j)/K] = 0;
            lazy[j/K] = -1;
            amx[j/K] = a[j];
        }
        pre[(j)/K] = max(pre[(j)/K], a[j] - mi);
        mi = min(mi, a[j]);
        ami[j/K] = mi;
        amx[j/K] = max(amx[j/K], a[j]);
    }
    // rep(j, 0, K)
    //     cout << j <<' ' << pre[j] << '\n';
}

int ask(int l, int r)
{
    // if(l%K != 0)
    // {
        push(l/K);
        updt(l/K);
    // }
    int rs = 0, mi = a[l];
    // cout << l << ' ' << l%K << '\n';
    while(l%K != 0 && l <= r)
    {
        rs = max(rs, a[l]-mi);
        mi = min(mi, a[l++]);
    }
    while(l+K-1 <= r)
    {
        // cout << "OPA " << l << ' ' << pre[l/K] << ' ' << amx[l/K] << "\n"; 
        rs = max(rs, pre[l/K]);
        rs = max(rs, amx[l/K]-mi);
        mi = min(mi, ami[l/K]);
        l+=K;
    }
    // cout << l << ' ' << r << ' ' << rs << "<<<\n";
    if(l <= r){
        push(l/K);
        updt(l/K);
        // cout << rs << "<<<<\n";
        while(l <= r)
        {
            // cout << a[l] << ' ';
            rs = max(rs, a[l]-mi);
            mi = min(mi, a[l++]);
        }
        // cout << '\n';
    }
    return rs;
}

void updt(int l, int r, int k)
{
    int id = calc(l, k);
    if(l%K != 0)
    {
        push(l/K);
        while(l%K != 0 && l <= r)
        {
            a[l++] = b[k++];
        }
        updt((l-1)/K);
    }
    while(l+K-1 <= r)
    {
        // cout << l << ' ' << k << "<<<\n";
        // cout << id << ' ' << pre[l/K] << ' ' << ans[id][(k-id)/K] << '\n';
        pre[l/K] = ans[id][(k-id)/K];
        amx[l/K] = bmx[id][(k-id)/K];
        ami[l/K] = bmi[id][(k-id)/K];
        lazy[l/K] = k;
        l+=K;
        k+=K;
    }
    if(l <= r)
    {
        // cout << l << ' ' << k << "<<<<<<<\n";
        push(r/K);
        while(l <= r)
            a[l++] = b[k++];
        updt(r/K);

    }
}

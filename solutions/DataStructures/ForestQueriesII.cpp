#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
 
const int N = 1010;
 
int bit[N][N], a[N][N];
 
void updt(int x,int y,int v)
{
    if(!v)
        return;
    for(int i = x; i < N; i+=(i&-i))
    {
        for(int j = y; j < N; j+=(j&-j))
        {
            bit[i][j] += v;
        }
    }
}
int query(int x,int y)
{
    int v = 0;
    if(!x || !y)
        return 0;
    for(int i = x; i ; i-=(i&-i))
    {
        for(int j = y; j; j-=(j&-j))
        {
            v += bit[i][j];
        }
    }
    return v;
}
 
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    string s;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> s;
        for(int j = 1; j <= n; j++)
        {
            if(s[j-1] == '*'){
                a[i][j] = 1;
                updt(i, j, 1);
            }
        }
    }
    
    for(int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int x, y;
            cin >> x >> y;
            updt(x, y, -a[x][y]);
            a[x][y] ^= 1;
            updt(x, y, a[x][y]);
        }else
        {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1) << '\n';
        }
    }
    return 0;
}
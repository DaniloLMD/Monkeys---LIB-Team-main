#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000010;
const ll mod = 1000000007LL;
int dp[N];
int mex(set<int> s)
{
    int x = 0;
    while(s.find(x) != s.end())
        x++;
    return x;
}
int grundy(int n)
{
    if(n <= 2)
        return 0;
    if(dp[n]!=-1)
        return dp[n];
    set<int> s;
    for(int i = 1; i + i < n; i++)
    {
        s.insert(grundy(i)^grundy(n-i));
    }
    return dp[n] = mex(s);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    memset(dp,-1,sizeof(dp));
    // for(int i = 1; i <= 50000; i++){
    //     if(grundy(i) == 0 )
    //         cout << i << endl;
    // }
    // cout << '\n';
    int q;
    cin >> q;
    while(q--)
    {
        int n;
        cin >> n;
        if(n > 1222)
            cout << "first\n";
        else
            cout << (grundy(n)?"first\n":"second\n");
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define el '\n'
using ll = long long int;
template<class T> using vc = vector<T>; template<class T> using vvc = vector<vc<T>>;
 
// modint
 
void test(){
    int n,x; cin >> n >> x;
    int mais = 5e3;
    vc<int> a(n); for(int i=0; i<n; i++) cin >> a[i];
    sort(a.begin(),a.end());
    vvc<mi> dp((n>>1)+1,vc<mi>((mais<<1)+10,0));
    int t1 = dp.size(), t2 = dp[0].size();
    vvc<mi> ot = dp;
    dp[0][mais] = 1;
    for(int i=0; i<n; i++){
        swap(dp,ot);
        for(int j=0; j<t1; j++) for(int k=0; k<t2; k++) dp[j][k] = 0;
        // primeiro termo eh adicionar o elemento em um dos grupos ou 
        //criar um grupo so com o cara
        // o segundo termo eh criar um grupo e subtrair o valor do 
        //cara na soma total
        // o terceiro termo eh fechar um grupo e soma o valor do cara 
        //na soma total
        for(int qt=0; qt<t1; qt++) for(int s=0; s<t2; s++)
        dp[qt][s] = (qt+1)*ot[qt][s] 
        + (qt && s+a[i]<t2 ? ot[qt-1][s+a[i]] : 0)
        + (qt+1)*(qt+1<t1 && s-a[i]>=0 ? ot[qt+1][s-a[i]] : 0);
    }   
    mi ans = 0;
    for(int s=mais; s<t2 &&  s-mais <= x; s++) ans += dp[0][s];
    cout << ans << el;
}
 
int main (){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
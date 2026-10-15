// https://codeforces.com/group/s9DkvFL2Hl/contest/625231
#include <bits/stdc++.h>
using namespace std;
#define get_bit(x,i) ((x)&(1ll<<(i)))
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
using ll = long long int;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAX = 5e4 + 10;
const ll inf = (1ll<<62) + (1ll<<61) + (1ll<<60);

ll a[MAX],cnt[MAX],dp[MAX],ot[MAX],sum = 0;
ll cost(int id){
    return cnt[a[id]] * cnt[a[id]] * a[id] * a[id];
}
void add(int id){
    sum -= cost(id);
    cnt[a[id]]++;
    sum += cost(id);
}
void rmv(int id){
    sum -= cost(id);
    cnt[a[id]]--;
    sum += cost(id);
}

void solve(int l,int r, int otl,int otr){
    if(l > r) return;
    int mid = l + r; mid >>= 1;
    pair<ll,int> bst = {inf,-1}; // value and opt(mid)
    // pegar os valores que eu ainda nao considerei na chamada acima de mim
    for(int j=mid; j>=max(l,otr+1); j--) add(j);
    for(int j=min(mid,otr); j>=otl; j--){
        add(j);
        bst = min(bst,{sum+ot[j-1],j});
    }
    for(int j=mid; j>=max(l,otr+1); j--) rmv(j);
    for(int j=min(mid,otr); j>=otl; j--) rmv(j);
    dp[mid] = bst.first;
    
    // chama pras outras metades
    for(int j=min(l-1,otr); j>bst.second; j--) add(j);
    solve(l,mid-1,otl,bst.second);
    for(int j=min(l-1,otr); j>bst.second; j--) rmv(j);
    
    for(int j=mid; j>=max(l,otr+1); j--) add(j);
    solve(mid+1,r,bst.second,otr);
    for(int j=mid; j>=max(l,otr+1); j--) rmv(j);
}

void test(){
    /*
        O problema pode ser modelado como dp[i][j] = menor custo usando
    i segmentos e considerando os j primeiros elementos. Temos que
        dp(i,j) = min_{k < j}(dp(i-1,k) + C(k+1,j)) 
        Tal que C eh o custo do segmento da range (k+1,j). Vamos 
    calcular  a DP e quando formos diminuir na range vamos usar a funcao 
    de custo calculada de outras chamadas do D&C pra calcular a funcao 
    de custo pras ranges menores do Divide and Conquer.
    */
    int n,c;
    cin >> n >> c;
    for(int i=1; i<=n; i++) cin >> a[i];
    // escolhemos o primeiro segmento
    for(int i=1; i<=n; i++) {
        add(i);
        dp[i] = sum;
    }
    // resetemos o custo
    for(int i=1; i<=n; i++) rmv(i);
    for(int j=2; j<=c; j++) {
        for(int i=1; i<=n; i++) ot[i] = dp[i];
        solve(1,n,1,n);
    }
    cout << dp[n] << '\n';
}  

int main (){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
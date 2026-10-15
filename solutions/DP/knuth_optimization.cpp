// https://codeforces.com/gym/102215/problem/G
#include <bits/stdc++.h>
using namespace std;
#define el '\n'
using ll = long long int;
const int MAX = 1e2+10;
ll a[MAX],pref[MAX];
ll dp[MAX][MAX],ot[MAX][MAX];
int opt_ot[MAX][MAX],opt[MAX][MAX];

void test(){
    /*
        Problema de Huffman, mas alem dos valores voce quer que a 
	profundidade maxima da arvore nao ultrapasse K, dai vc pode resolver 
	ele com uma DP de intervalo com os valores ordenados, porque sempre 
	existe uma  configuracao otima em que as folhas (os valores originais) 
	estao ordenadas. Dai o problema eh so decidir como a arvore binaria vai 
	estar disposta. Dai fica:
		DP[l][r] = min(DP[l][mid] + DP[mid+1][r] + (pref[r]-pref[l-1])). 
		Essa DP pode ser otimizada com Knuth. Dai pra resolver o nosso 
	problema, a unica coisa a mais eh adicionar o estado da profundidade 
	maxima da arvore ate agora. Dai so fica:
		DP[dep][l][r] = min(DP[dep-1][l][mid] + DP[dep-1][mid+1][r] + (pref[r]-pref[l-1])).
    	Que dai fica tudo O(n^3) e passa clean.
    */
    int n,k; cin >> n >> k;
    for(int i=0; i<n; i++) cin >> a[i];
    sort(a,a+n);
    for(int i=0; i<n; i++) pref[i] = (i ? pref[i-1] : 0) + a[i];
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) dp[i][j] = -1;
    for(int i=0; i<n; i++) dp[i][i] = 0;
    for(int i=0; i<n; i++) opt[i][i] = i;
    ll ans = -1;
    for(int t=1; t<=k; t++){
        for(int i=0; i<n; i++) for(int j=0; j<n; j++){
            ot[i][j] = dp[i][j];
            opt_ot[i][j] = opt[i][j];
        }   
        for(int tam=2; tam<=n; tam++) for(int l=0; l+tam<=n; l++){
            int r = l+tam-1;
            pair<ll,int> bst(-1,-1);
            for(int mid=opt[l][r-1]; mid <= min(r-1,opt[l+1][r]); mid++) if(ot[l][mid] != -1 && ot[mid+1][r] != -1){
                pair<ll,int> aux(ot[l][mid] + ot[mid+1][r] + pref[r]-(l ? pref[l-1] : 0),mid);
                bst = (bst.first == -1 ? aux : min(bst,aux));
            }
            dp[l][r] = bst.first, opt[l][r] = bst.second;
        }
        ans = (ans == -1 ? dp[0][n-1] : (dp[0][n-1] == -1 ? ans : min(ans,dp[0][n-1])));
    }
    if(ans == -1) cout << "No solution" << el;
    else{
        ll g = __gcd(pref[n-1],ans);
        cout << ans/g << '/' << pref[n-1]/g << el;
    }
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int tt = 1;
    // cin >> tt;
    while(tt--) test();
    return 0;
}
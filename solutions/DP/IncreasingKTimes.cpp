#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using vi = vector<int>; using vl = vector<ll>;
const ll mod = 998244353;

void test(){
    /*
        Podemos enxergar esse problema como: eu tenho um vetor e eu 
    posso ordena-lo do jeito que eu quiser, qual a quantidade de 
    ordenacoes tal que exatamente K posicoes obedecem V[i] < V[i+1]? 
    Usando o Trick 2, vamos adicionando os menores elementos de A[i] 
    e suponha que em algum momento temos X posicoes em que V[i] < V[i+1] 
    (V eh o vetor que eu vou construindo), se vc colocar o novo elemento 
    entre i e i+1, vamos ter que V[i] < VAL >= V[i+1], ou seja, nao 
    alteramos a qtd total X de posicoes em que V[i] < V[i+1], tambem 
    nao alteramos se colocamos o valor VAL no inicio ou depois de outras 
    posicoes em que V[i] == VAL, pois V[i] == VAL e, como VAL eh o 
    ultimo elemento que vc colocou ate agora, temos que VAL >= V[i+1]. 
    Dai eh so fazer a DP.
    */
    int n,k; cin >> n >> k;
    vi a(n); for(int i=0; i<n; i++) cin >> a[i];
    sort(a.begin(),a.end());
    vector<vl> dp(n+10,vl(k+10,0));
    dp[1][0] = 1; int eq = 0;
    for(int i=2; i<=n; i++){
        eq = (a[i-1] != a[i-2] ? 0 : eq+1);
        for(int j=0; j<=k; j++){
            // posso colocar no a_{i-1} < a_i, no inicio e depois de um cara igual a eu que nao vai mudar
            dp[i][j] = (dp[i][j] + dp[i-1][j] * (j+eq+1) % mod) % mod;
            // colocar em qualquer outro lugar aumenta a qtd de caras que sao maiores
            if(j) dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (i+1 - (j+eq+1)) % mod) % mod; 
        }
    }
    cout << dp[n][k] << '\n';
}

int main (){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
// https://codeforces.com/group/btcK4I5D5f/contest/623901/problem/K
#include <bits/stdc++.h>
using namespace std;
#define el '\n'
using ll = long long int; using ull = uint64_t; using ld = long double;
template<class T> using vc = vector<T>; template<class T> using vvc = vector<vc<T>>;

// modint

void test(){
    /*
        Vamos considerar dp[N][K] a quantidade de permutacoes com N
    elementos tal que existem K posicoes onde p[i] >= i. Assim dp[N] vai 
    conter todas as permutacoes de N elementos, vamos inserir o proximo 
    elemento N+1, dai dependendo de quem com quem vc swapa esse cara a 
    quantidade K de posicoes vai mudar, dai eh so considerar uns casos e
    voce vai chegar em:
        dp[N+1][K] = dp[N][K-1] * (i-1-(k-1)+1) + dp[K]*K, 
    o primeiro termo eh colocar o N+1 numa posicao em que p[i]<i ou 
    colocar o N+1 na ultima posicao e aumentar o valor de K, o segundo 
    termo eh trocar o N+1 por uma posicao em que p[i] >= i e o valor de 
    K vai se manter.
    */
    int n; cin >> n;
    vc<mi> dp(n+10,0);
    dp[1] = 1;
    // dp[k] = dp[k-1] * (i-1-(k-1)+1) + dp[k] * k
    for(int i=2; i<=n; i++){
        for(int k=n; k>0; k--) dp[k] = dp[k-1] * (i-1-(k-1)+1) + dp[k] * k;
    }
    for(int i=1; i<=n; i++) cout << dp[i] << ' ';
    cout << el;
}

int main (){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
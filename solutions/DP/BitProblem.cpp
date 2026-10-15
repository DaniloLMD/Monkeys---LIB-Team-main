#include <bits/stdc++.h>
using namespace std;
#define get_bit(x,i) ((x)&(1ll<<(i)))
const int MAX = 2e5+10;
const int MAX_S = (1<<20) + 10;

int a[MAX],cnt[MAX_S],cnt_inv[MAX_S],dp[MAX_S][3];

int inv(int x){
    return ((1<<20)-1)^x;
}

// so faz o SOS
void solve0(){
    for(int msk = 0; msk<(1<<20); msk++) dp[msk][0] = cnt[msk];
    for(int j=0; j<20; j++)
        for(int msk = (1<<20)-1; msk >= 0; msk--) 
            if(get_bit(msk,j)) dp[msk][0] += dp[msk^(1<<j)][0];
}

// contar os super conjuntos eh analogo a contar se o complemento do conjunto 
// eh ver se o complemento engloba o outro, dai eh super-conjunto
void solve1(){
    for(int i=0; i<(1<<20); i++) cnt_inv[inv(i)] = cnt[i];
    for(int msk = 0; msk<(1<<20); msk++) dp[msk][1] = cnt_inv[msk];
    for(int j=0; j<20; j++)
        for(int msk = (1<<20)-1; msk >= 0; msk--) 
            if(get_bit(msk,j)) dp[msk][1] += dp[msk^(1<<j)][1];
    for(int msk=0; msk<(1<<20); msk++) 
        if(inv(msk) > msk) swap(dp[msk][1],dp[inv(msk)][1]);
}

// aqui eu to contando pra cada elemento quantos elementos vao ter interseccao nula
// pra fazer isso eu transito usando o conjunto complementar, pq se dois conjuntos sao disjuntos, 
// o complementar de um deles contem o outro conjunto e vice-versa, entao eu guardo
// dp[msk] = quantos conjuntos o meu inverso contem, dai a transicao eh pensando no inverso
void solve2(){
    for(int msk = 0; msk<(1<<20); msk++) dp[msk][2] = cnt[inv(msk)];
    for(int j=0; j<20; j++){
        for(int msk = (1<<20)-1; msk >= 0; msk--) {
            int ot = inv(msk);
            if(get_bit(ot,j)) dp[msk][2] += dp[inv(ot^(1<<j))][2];
        }
    } 
}

void test(){   
    int n; cin >> n;
    for(int i=0; i<n; i++) cin >> a[i];
    for(int i=0; i<n; i++) cnt[a[i]]++;
    solve0(), solve1(), solve2();
    for(int i=0; i<n; i++) cout << dp[a[i]][0] << ' ' << dp[a[i]][1] << ' ' << n - dp[a[i]][2] << '\n';
}

int main (){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
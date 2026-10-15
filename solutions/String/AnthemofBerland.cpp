// https://codeforces.com/contest/808/problem/G
#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

const int MAX = (int) 2e5 + 10;
const int mod = (int) 1e9 + 7;

int p[MAX];
int aut[MAX][30];
string s,t;

bool eq(char a, char b){
    if(a == b) return true;
    if(a == '#' || b == '#') return false;
    if(a == '?' || b == '?') return true;
    return false;
}

void kmp(string & str){
    int n = str.size();
    p[0] = 0;
    for(int i=1; i<str.size(); i++){
        int j = p[i-1];
        while(j != 0 && !eq(str[i],str[j])) j = p[j-1];
        if(eq(str[i], str[j])) j++;
        p[i] = j;
    }
    // no automato sempre vamos tentar andar pra frente, se nao der pra ir pra frente dai a gente vai pra tras
    // i == 0 representa a string vazia

    for(int i=0; i<n; i++){
        for(int j='a'-'a'; j<='z'-'a'; j++){
            if(i == 0) aut[i][j] = (str[i] == j + 'a');
            else if(str[i] == 'a' + j) aut[i][j] = i+1; // se essa posicao eh igual ao caracter que eu quero ir, entao eu consigo dar match de caracter e ir pra proxima posicao
            else aut[i][j] = aut[p[i-1]][j]; // vou pro maior prefixo que eh comum ao sufixo do atual e uso a transicao dele
        }
    }
}

int solve(int i,int j, vector<vector<int>> & dp){
    if(i == s.size()) return (j == t.size()-1);
    if(dp[i][j] != -1) return dp[i][j];
    dp[i][j] = (j == t.size()-1);
    int ot = 0;
    if(s[i] != '?') ot = solve(i+1,aut[j][s[i]-'a'],dp);
    else{
        for(int c=0; c<30; c++) ot = max(ot, solve(i+1,aut[j][c],dp));
    }
    dp[i][j] += ot;
    return dp[i][j];
}

void test(){
    /*
        Vamos fazer uma DP[N][M] tal que N eh a posicao na string texto (STR) e M eh a posicao no pattern (PAT). Dai imagina que tamo em DP[i][j], se STR[i] != '?',
    entao a transicao eh "deterministica", se STR[i] == PAT[j], entao transitamos para DP[i+1][j+1], mas se STR[i] != PAT[j], vamos transitar para uma posicao do PAT
    que nao eh j+1, dai parece que nesse caso vc teria que voltar nos estados pra conseguir um estado em que o k-esimo caracter de PAT eh igual a STR[i] e dai continuar
    a transicao dai, ou seja, imagina que fosse cacd a string texto e o pattern fosse caca, dai imagina que estivessemos comparando o 'd' com o ultimo 'a', dai a gente
    teria que voltar em transicoes e comparar o 'ca' da string texto com o sufixo 'ca' do pattern, dai isso eh andar no maior sufixo que eh comum do pattern, dai pra
    fazer isso, usamos KMP, construimos um automato pra cada cada estado (posicao da string) considerarmos cada transicao possivel (adicionar um novo caracter). Dai
    construir o automato eh (N+M)*26 e a dp eh N*M*26, pq pra cada interrogacao temos 26 transicoes, uma pra cada caracter.
    */
    cin >> s >> t;
    t.push_back('#');
    kmp(t);
    vector<vector<int>> dp(s.size()+1, vector<int>(t.size()+1,-1));
    cout << solve(0,0,dp) << '\n';
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
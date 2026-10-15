// https://codeforces.com/gym/105950/problem/C
#include <bits/stdc++.h>
using namespace std;
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define get_bit(x,i) ((x)&(1ll<<(i)))
#define bshift(i) (1ll<<(i))

using ull = unsigned long long int;
using ll = long long int;

const int MAX = (int) 2e3 + 10;
const int TETO = 13;

/*
    Sempre chamar o build depois que inserir todas as strings pra construir o automato
*/
const int ALP = 26; // tamanho do alfabeto
struct node{
    int prox[ALP] = {0}, aut[ALP] = {0};
    int p = 0, ep = 0; // kmp like, kmp like with end of string
    bool fim = false;
    node(){}
    int& operator[](int x){return prox[x];}
    int& operator()(int x){return aut[x];}
    int qt = 0;
    // vector<int> ids; // sometimes put id of each string end
};
vector<node> trie(1);
void insert(string & s, int id){
    int at = 0;
    for(char c : s){
        c -= 'a'; // int& prox = trie[at].prox[c] eh paia pq no emplace_back() o ponteiro vai dar pau
        if(trie[at][c] == 0) {
            trie[at][c] = int(trie.size());
            trie.emplace_back();
        }
        at = trie[at][c];
    }
    trie[at].qt++;
    trie[at].fim = true;
}
void build(){
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int *prox = trie[u].prox, *aut = trie[u].aut;
        int p = trie[u].p;
        for(int c=0; c<ALP; c++){
            if(prox[c] != 0){
                int v = prox[c];
                aut[c] = v;
                q.push(v);

                trie[v].p = (u == 0 ? 0 : trie[p](c)); // ja calcular o link dos prox caras
            }else if(u == 0) aut[c] = 0;
            else aut[c] = trie[p](c);
        }
        if(trie[p].fim) trie[u].ep = p;
        else trie[u].ep = trie[p].ep;

        trie[u].qt += trie[p].qt;
    }
}

string p[MAX];
int jmp[MAX][MAX][TETO];
int qt[MAX][MAX][TETO];
int dp[MAX][MAX][2];
int N;
string s;

pair<int,int> get(int pos,int at, int tam){
    int qtd = 0;
    for(int t=TETO-1; t>=0; t--){
        if(get_bit(tam,t)){
            tam -= bshift(t);
            qtd += qt[pos][at][t];
            int prox = pos - bshift(t);
            int v = jmp[pos][at][t];
            pos = prox, at = v;
        }
    }
    return {at,qtd};
}

int solve(int i,int at, int f){
    if(i == N) return trie[at].qt;
    int & bst = dp[i][at][f];
    if(bst != -1) return bst;
    bst = solve(i+1,trie[at].aut[s[i]-'a'],f) + trie[at].qt;
    if(!f){
        for(int j=i+1; j<N; j++){
            auto [v,qtd] = get(j,at,j-i+1);
            bst = max(bst, qtd + solve(j+1,v,1));
        }
    }
    return bst;
}

void test(){
    /*
        Podemos fazer uma dp com automato, estou na posicao I da string, na posicao AT do automato e com uma flag F se eu ja inverti uma substring ou nao, dai se F == 0
    (nao inverti a uma substring), ou eu continuo normal dp = solve(I+1, trie[AT].aut[s[I]-'a'],f) trie[at].qt, ou eu escolho alguma posicao pra inverter com essa:
        for(int j=I+1; j<N; j++){
            int qtd = 0;
            for(int k=j; k>=I; k--){
                qtd += trie[AT].qt;
                AT = trie[AT].aut[s[k]-'a']; 
            }
            dp = max(dp, solve(j+1,AT,1));
        }
        Se F == 1, entao a unica opcao eh continuar indo pra frente, mas desse jeito a complexidade n fica N^4? Pq temos N^2 estados e pra cada estado temos dois loops
    aninhados, mas n eh, pq os dois loops aninhados so acontecem enquanto F == 0, mas quando F == 0, os estados sao deterministicos, ou seja, o AT nao tem diferenca nenhuma,
    pra um I sempre vai ter um AT se F == 0. Dai ficaria N^3 na true, pq pros N estados em que F == 0, temoos dois loops aninhados. Mas isso eh lento, dai o trick eh fazer
    um binary lifting no automato. 
        Pra cada par, posicao I da string e posicao AT no automato vamos fazer um binary lifting que eh, qual estado do automato eu vou estar se eu comecar na posicao I
    e AT com pulo de tamanho 2^T e guardar isso em jmp[I][AT][T], alem disso guardar o somatorio das qtd nos automatos nos pulos em qt[I][AT][T]. Esse esquemas da qtd de
    automato eh contar quantas strings terminam na posicao AT do automato dai eh so andar nos maiores sufixos e guardar as quantidades que terminam nessas posicoes do
    automato. Com o binary lifting, podemos tirar o loop interno e fazer ele em log(N), dai a complexidade final fica N^2 * log(N).
    */
    cin >> s;
    int n;
    cin >> n;
    N = s.size();
    for(int i=0; i<n; i++) cin >> p[i];
    for(int i=0; i<n; i++) insert(p[i]);
    build();
    for(int t=0; t<TETO; t++){
        for(int i=0; i<s.size(); i++){
            for(int at=0; at<trie.size(); at++){
                if(t == 0){
                    int c = s[i] - 'a';
                    jmp[i][at][0] = trie[at](c);
                    qt[i][at][0] = trie[at].qt;
                }else if(i - bshift(t-1) >= 0){
                    int z = jmp[i][at][t-1];
                    jmp[i][at][t] = jmp[i-bshift(t-1)][z][t-1];
                    qt[i][at][t] = qt[i-bshift(t-1)][z][t-1] + qt[i][at][t-1];
                }
            }
        }
    }
    memset(dp,-1,sizeof(dp));
    cout << solve(0,0,0) << '\n';
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
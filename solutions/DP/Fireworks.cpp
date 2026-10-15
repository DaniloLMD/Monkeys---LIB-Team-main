// Fireworks: https://oj.uz/problem/view/APIO16_fireworks
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long int;
 
const int MAX = (int) 3e5 + 10;
 
struct SlopeTrick{
    struct Function{
        ll a = 0,b = 0;
        void operator +=(Function & ot){
            a += ot.a;
            b += ot.b;
        }
    };
    priority_queue<ll> pts; // slope change
    Function f; // last linear function
 
    // seja A a funcao antes de considerar a aresta Z
    // seja B a funcao de custo da aresta Z (B(x) = abs(x-z))
    // queremos computar C, tal que C(x) = min(A(x-x') + B(x'))
    /*
        O menor valor de C vai ser os pontos que tem inclinacao zero 
    com A, vamos chamar de regiao (La,Ra), somado com o zero de B que 
    eh X = Z, isso vai gerar uma regiao de pontos com melhor valor 
    (La+Z,Ra+Z), agora vamos calcular o melhor valor possivel para 
    X = La+Z-1. O melhor valor disso seria usar X = La de A e X = Z-1 
    de B ou usar X = La-1 de A e X = Z de B, mas vamos considerar a 
    primeira opcao, pq nao sabemos ate que ponto de A, a inclinacao da 
    reta vai ser -1. Mas desse jeito so podemos usar a funcao de B ate 
    X = 0, pq nao podemos diminuir o valor da aresta para um custo 
    negativo, entao no maximo so podemos usar X = 0 de B. Isso vai gerar 
    uma regiao (La,La+Z) com inclinacao -1 e uma regiao de (La+Z,Ra+Z) 
    com inclinacao 0 usando o ponto X = La. E olhando pro resto a 
    inclinacao dos pontos com o slope changing points vao ser os mesmos 
    da funcao A, dai nem precisa mudar eles
    */
    void arruma(int z){
        if(pts.empty()){
            f.a = 1;
            f.b = -z;
            pts.push(z);
            pts.push(z);
            return;
        }
        ll lst=0;
        while(f.a != 0){
            ll x = pts.top();
            pts.pop();
            ll y = f.a*x + f.b;
            f.a--;
            f.b = y - f.a*x;
            lst = x;
        }
 
        ll lst2 = pts.top();
        pts.pop();
        pts.push(lst2 + z); 
        pts.push(lst + z);
 
        // considerar a nova inclinacao 1
        f.a++;
        f.b = f.b - f.a*(lst+z);
    }
    ll solve(){
        while(f.a != 0){
            ll x = pts.top();
            pts.pop();
            ll y = f.a*x + f.b;
            f.a--;
            f.b = y - f.a*x;
        }
        return f.b;
    }
    void show(){
        priority_queue<ll> pq = pts;
        Function g = f;
        while(!pq.empty()){
            ll x = pq.top();
            pq.pop();
            cout << x << ' ' << g.a << ' ' << g.b << endl;
            ll y = g.a*x + g.b;
            g.a--;
            g.b = y - g.a*x;
        }
        cout << "-inf " << g.a << ' ' << g.b << endl;
    }
};
 
vector<pair<int,int>> graph[MAX];
int rep[MAX];
SlopeTrick slp[MAX];
 
int get(int u){return rep[u] = rep[u] == u ? u : get(rep[u]);}
void merge(int u,int v){
    u = get(u), v = get(v);
    if(u  == v) return;
    if(slp[u].pts.size() < slp[v].pts.size()){
        merge(v,u);
        return;
    }
    auto & at = slp[u];
    auto & ot = slp[v];
    while(!ot.pts.empty()){
        ll x = ot.pts.top();
        ot.pts.pop();
        at.pts.push(x);
    }
    at.f += ot.f;
    rep[v] = u;
}
 
void solve(int u,int ant){
    for(auto [v,z] : graph[u]){
        if(v == ant) continue;
        solve(v,u);
        slp[get(v)].arruma(z);
        merge(u,v);
    }
}
 
void test(){
    /*
        Vamos resolver o problema pra cada subarvore e dar um merge nas 
    respostas de cada subarvore, dai se tivesse so uma aresta vamos 
    definir dp(x) como o custo para fazer o edge ter o custo x, temos 
    que dp(x) = |x - z| tal que z eh o peso original da aresta. Quando 
    dermos merge, vamos dar merge de slope-trickable functions e dai 
    usar small to large dos containers do slope trick.
    */
    int n,m;
    cin >> n >> m;
    for(int i=1; i<=n+m; i++) rep[i] = i;
    for(int i=2; i<=n+m; i++){
        int x,z;
        cin >> x >> z;
        graph[x].push_back(make_pair(i,z));
        graph[i].push_back(make_pair(x,z));
    }
    solve(1,1);
    cout << slp[get(1)].solve() << '\n';
}
 
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttt_ = 1;
    // cin >> ttt_;
    while(ttt_--) test();
    return 0;
}
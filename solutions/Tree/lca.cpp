// LCA com RMQ
//
// Assume que um vertice eh ancestral dele mesmo, ou seja,
// se a eh ancestral de b, lca(a, b) = a
// dist(a, b) retorna a distancia entre a e b
//
// Complexidades:
// build - O(n)
// lca - O(1)
// dist - O(1)

template<typename T> struct rmq {
	vector<T> v;
	int n; static const int b = 30;
	vector<int> mask, t;

	int op(int x, int y) { return v[x] < v[y] ? x : y; }
	int msb(int x) { return __builtin_clz(1)-__builtin_clz(x); }
	rmq() {}
	rmq(const vector<T>& v_) : v(v_), n(v.size()), mask(n), t(n) {
		for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
			at = (at<<1)&((1<<b)-1);
			while (at and op(i, i-msb(at&-at)) == i) at ^= at&-at;
		}
		for (int i = 0; i < n/b; i++) t[i] = b*i+b-1-msb(mask[b*i+b-1]);
		for (int j = 1; (1<<j) <= n/b; j++) for (int i = 0; i+(1<<j) <= n/b; i++)
			t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
	}
	int small(int r, int sz = b) { return r-msb(mask[r]&((1<<sz)-1)); }
	T query(int l, int r) {
		if (r-l+1 <= b) return small(r, r-l+1);
		int ans = op(small(l+b-1), small(r));
		int x = l/b+1, y = r/b-1;
		if (x <= y) {
			int j = msb(y-x+1);
			ans = op(ans, op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
		}
		return ans;
	}
};

namespace lca {
	vector<int> g[MAX];
	int v[2*MAX], pos[MAX], dep[2*MAX];
	int t;
	rmq<int> RMQ;

	void dfs(int i, int d = 0, int p = -1) {
		v[t] = i, pos[i] = t, dep[t++] = d;
		for (int j : g[i]) if (j != p) {
			dfs(j, d+1, i);
			v[t] = i, dep[t++] = d;
		}
	}
	void build(int n, int root) {
		t = 0;
		dfs(root);
		RMQ = rmq<int>(vector<int>(dep, dep+2*n-1));
	}
	int lca(int a, int b) {
		a = pos[a], b = pos[b];
		return v[RMQ.query(min(a, b), max(a, b))];
	}
	int dist(int a, int b) {
		return dep[pos[a]] + dep[pos[b]] - 2*dep[pos[lca(a, b)]];
	}
}

// LCA com binary lifting
//
// Indexado de 1.
// As vezes mudar o calc do LCA, setar o TETO = teto de log2(n).
// build - O(nlog(n))
// lca - O(log(n))
// calc - O(log(n))
struct LCA{
    struct info{
        int p;
    };
    int n,timer; // qtd de vertices,timer
    vector<vector<int>> &graph; // grafo original
    // entrada, saida, e euler tour 
    vector<int> tin,tout,euler;
    int flag; // (flag == 1 ? tin != tout : tin == tout)
    vector<int> dist; // distancia de cada cara pra raiz
    vector<vector<info>> pai; // tabela de ancestrais
    int r; // raiz da arvore
    const int TETO = ; // teto(log2(n))

    LCA(int nn, vector<vector<int>> &ggraph, int fflag=0, int rr=1) : n(nn), graph(ggraph),tin(nn+1),tout(nn+1),euler(fflag ? 2*n+1 : n+1),
    dist(n+1),pai(n+1,vector<info>(TETO)), r(rr){
        build(r,r);
    }

    void build(int u,int ant){
        if(u == ant) dist[u]=0;
        else dist[u]=dist[ant]+1;
        
        // construir tabela de ancestrais
        pai[u][0]={ant};
        for(int i=1; i < TETO; i++) {
            pai[u][i].p = pai[pai[u][i-1].p][i-1].p;
        }
        
        tin[u]=++timer;
        for(auto v: graph[u]){
            if(v == ant) continue;
            build(v,u);
        }
        
        tout[u]=(flag ? ++timer : timer);
    }

    // x eh lca de y?
    bool lca(int x,int y){
        return tin[x] <= tin[y] && tout[x] >= tout[y];
    }

    // calcula alguma coisa, deixei como se fosse dist, entre x e y
    int calc(int x,int y){
        if(lca(x,y)) return dist[y]-dist[x];
        else if(lca(y,x)) return dist[x]-dist[y];
        int z=x;
        for(int i=TETO-1; i>=0; i--){
            if(!lca(pai[z][i].p,y)) z=pai[z][i].p;
        }
        z=pai[z][0].p;
        return dist[x]+dist[y]-2*dist[z];
    }
    // calcula lca entre x e y
    int calc_lca(int x,int y){
        if(lca(x,y)) return x;
        else if(lca(y,x)) return y;
        int z=x;
        for(int i=TETO-1; i>=0; i--){
            if(!lca(pai[z][i].p,y)) z=pai[z][i].p;
        }
        z = pai[z][0].p;
        return z;
    }
};
// Li-Chao Tree - Lazy . Baseado na lib da UFMG
//
// TX = tipo das coordenadas (x, y, l, r, MI, MA) 
// TC = tipo dos coeficientes (a, b)              
//
// Sendo N = MA-MI
// insert({a, b, id})       - minimiza tudo com ax+b - O(log N)
// insert({a, b, id}, l, r) - minimiza com ax+b no range [l, r] - O(log^2 N)
// shift({a, b})            - soma ax+b em tudo - O(1)
// shift({a, b}, l, r)      - soma ax+b no range [l, r] - O(log^2 N)
// query(x)                 - retorna {y, id} da reta com menor y na posicao x - O(log N)
//
// No inicio eh tudo LINF  e id = -1), se inserir {0, 0, id} fica tudo 0 com aquele id
//
// ATENCAO: a complexidade O(log N) assume que TX eh um tipo "discreto"
// (int/long long), pois a recursao termina quando l == r. Se TX for
// ponto flutuante, a arvore pode nao terminar (l == r quase nunca ocorre
// exatamente); nesse caso, discretize as coordenadas antes de usar.
//
// O(n log N) de memoria ; O(n) de memoria se nao usar as operacoes de range

template<class TX = long long, class TC = long double>
struct lichao {
	struct line {
		TC a, b;
		TC la, lb; // lazy
		array<int, 2> ch;
		int id; // identificador da reta (-1 = nao definida)
		line(TC a_ = TC(0), TC b_ = TC(0), int id_ = -1) :
			a(a_), b(b_), la(TC(0)), lb(TC(0)), ch({-1, -1}), id(id_) {}
		TC operator ()(TX x) const { return a*x + b; }
	};
	vector<line> ln;
	TX MI, MA;
	TC LINF; 

	int ch(int p, int d) {
		if (ln[p].ch[d] == -1) {
			ln[p].ch[d] = ln.size();
			ln.emplace_back(TC(0), LINF, -1);
		}
		return ln[p].ch[d];
	}

	lichao(TX mi = TX(-1e9), TX ma = TX(1e9), TC linf = numeric_limits<TC>::max() / TC(2))
		: MI(mi), MA(ma), LINF(linf) {
		ln.emplace_back(TC(0), LINF, -1);
	}

	void prop(int p, TX l, TX r) {
		if (ln[p].la == TC(0) and ln[p].lb == TC(0)) return;
		ln[p].a += ln[p].la, ln[p].b += ln[p].lb;
		if (l != r) {
			int pl = ch(p, 0), pr = ch(p, 1);
			ln[pl].la += ln[p].la, ln[pl].lb += ln[p].lb;
			ln[pr].la += ln[p].la, ln[pr].lb += ln[p].lb;
		}
		ln[p].la = ln[p].lb = TC(0);
	}

	pair<TC,int> better(pair<TC,int> x, pair<TC,int> y) {
		return (y.first < x.first) ? y : x;
	}

	pair<TC,int> query(TX x, int p = 0, TX l = numeric_limits<TX>::min(), TX r = numeric_limits<TX>::min()) {
		if (p == 0 and l == numeric_limits<TX>::min() and r == numeric_limits<TX>::min()) l = MI, r = MA;
		prop(p, l, r);
		pair<TC,int> ret = {ln[p](x), ln[p].id};
		if (ln[p].ch[0] == -1 and ln[p].ch[1] == -1) return ret;
		TX m = l + (r-l)/2;
		if (x <= m) return better(ret, query(x, ch(p, 0), l, m));
		return better(ret, query(x, ch(p, 1), m+1, r));
	}

	void push(line s, int p, TX l, TX r) {
		prop(p, l, r);
		TX m = l + (r-l)/2;
		bool L = s(l) < ln[p](l);
		bool M = s(m) < ln[p](m);
		bool R = s(r) < ln[p](r);
		if (M) {
			swap(ln[p].a, s.a);
			swap(ln[p].b, s.b);
			swap(ln[p].id, s.id); 
		}
		if (s.b == LINF) return;
		if (L != M) push(s, ch(p, 0), l, m);
		else if (R != M) push(s, ch(p, 1), m+1, r);
	}

	void insert(line s, TX a, TX b, int p, TX l, TX r) {
		prop(p, l, r);
		if (a <= l and r <= b) return push(s, p, l, r);
		if (b < l or r < a) return;
		TX m = l + (r-l)/2;
		insert(s, a, b, ch(p, 0), l, m);
		insert(s, a, b, ch(p, 1), m+1, r);
	}
	void insert(line s) { insert(s, MI, MA, 0, MI, MA); }
	void insert(line s, TX a, TX b) { insert(s, a, b, 0, MI, MA); }

	void shift(line s, TX a, TX b, int p, TX l, TX r) {
		prop(p, l, r);
		TX m = l + (r-l)/2;
		if (a <= l and r <= b) {
			ln[p].la += s.a, ln[p].lb += s.b;
			return;
		}
		if (b < l or r < a) return;
		if (ln[p].b != LINF) {
			push(ln[p], ch(p, 0), l, m);
			push(ln[p], ch(p, 1), m+1, r);
			ln[p].a = TC(0), ln[p].b = LINF;
		}
		shift(s, a, b, ch(p, 0), l, m);
		shift(s, a, b, ch(p, 1), m+1, r);
	}
	void shift(line s) { shift(s, MI, MA, 0, MI, MA); }
	void shift(line s, TX a, TX b) { shift(s, a, b, 0, MI, MA); }
};

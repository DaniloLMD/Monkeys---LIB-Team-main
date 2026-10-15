// Indexado de 0
// Query com op associativa e update em range
// Query e update: 4*log(N)
// N*log(N) de memoria (cada update adiciona log(N)) (gasta MUITA memoria)
// Definir tudo que ta fora de Seg
// Nao ta muito bem testado XD
struct node{

    bool off = false;int l = 0,r = 0;
    node(){}
    friend void merge(node &x,node &y,node &at){
        if(x.off) return void(at = y);
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)
    }
};
struct upd{
    bool off = true;
    upd(){}
    // aplica upd
    friend void apply(node &at,upd &lazy,upd &x){
        if(at.off) // init node 
        // upd node
        if(lazy.off) // init lazy
        // upd lazy
        lazy.off = false;
    }
};
template <class node, class upd>
struct perSeg{
    #define lef(x) seg[x].l
    #define rig(x) seg[x].r
    perSeg(int nn = 0,vc<node> &v = {}) : n(nn),seg(1),lazy(1),rev(1,0){
        if(!v.empty()) build(0,0,n-1,v);
    }
    void init(vc<node> &v){
        assert(v.size() == n);
        build(0,0,n-1,v);
    }
    int n; vc<node> seg; vc<upd> lazy;
    vc<int> rev; // raiz da revisao
    node ret,aux;
    int get_rev(){return int(rev.size())-1;}
    void build(int u,int tl,int tr,vc<node>& v){
        if(tl == tr) return void(seg[u] = v[tl]);
        int tmid = tl + tr; tmid >>= 1;
        lef(u) = seg.size(); seg.emplace_back(), lazy.emplace_back();
        rig(u) = seg.size(); seg.emplace_back(), lazy.emplace_back();
        build(lef(u),tl,tmid,v),build(rig(u),tmid+1,tr,v);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    vc<node> b1;vc<upd> b2; // guarda nodes,upd criados no push
    vc<int> st;int timer; 
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u].off) return;
        if(timer == b1.size()) b1.emplace_back(),b2.emplace_back(),st.emplace_back();
        b1[timer] = seg[lef(u)], b2[timer] = lazy[lef(u)], st[timer++] = u;
        if(timer == b1.size()) b1.emplace_back(),b2.emplace_back(),st.emplace_back();
        b1[timer] = seg[rig(u)], b2[timer] = lazy[rig(u)], st[timer++] = u;
        apply(seg[lef(u)],lazy[lef(u)],lazy[u]), apply(seg[rig(u)],lazy[rig(u)],lazy[u]);
        lazy[u].off = true;
    }
    void unpush(int u,int tl,int tr){
        if(!timer || st[timer-1] != u) return;
        lazy[u].off = false;
        seg[rig(u)] = b1[--timer], lazy[rig(u)] = b2[timer];
        seg[lef(u)] = b1[--timer], lazy[lef(u)] = b2[timer];
    }
    void query(int u,int tl,int tr,int l,int r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        push(u,tl,tr); int tmid = tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(r,tmid)), query(rig(u),tmid+1,tr,max(l,tmid+1),r);
        unpush(u,tl,tr);
    }
    node query(int l,int r,int R){
        timer = 0,ret.off = true; query(rev[R],0,n-1,l,r);
        return ret;
    }
    void update(int u,int nu,int tl,int tr,int l,int r,upd &x){
        if(l > r) return;
        if(tl == l && tr == r) return apply(seg[nu],lazy[nu],x);
        lef(nu) = seg.size(); seg.emplace_back(seg[lef(u)]), lazy.emplace_back(lazy[lef(u)]);
        rig(nu) = seg.size(); seg.emplace_back(seg[rig(u)]), lazy.emplace_back(lazy[rig(u)]);
        push(nu,tl,tr); int tmid = tl + tr; tmid >>= 1;
        update(lef(u),lef(nu),tl,tmid,l,min(tmid,r),x),update(rig(u),rig(nu),tmid+1,tr,max(tmid+1,l),r,x);
        merge(seg[lef(nu)],seg[rig(nu)],seg[nu]);
    }
    void update(int l,int r,upd x,int R){
        timer=0,rev.emplace_back(seg.size()); seg.emplace_back(seg[rev[R]]),lazy.emplace_back(lazy[rev[R]]);
        update(rev[R],rev.back(),0,n-1,l,r,x);
    }
    #undef lef
    #undef rig
};
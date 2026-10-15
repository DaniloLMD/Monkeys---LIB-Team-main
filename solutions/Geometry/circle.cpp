// Circulos
//
// Operacoes relacionadas a circulos
#warning Incluir a base de geometria
struct circle{
    // centro da circuferencia, raio
    pt c;
    T r;
    circle(pt cc = {0,0}, T rr = 0) : c(cc), r(rr){}
};
// condicao: a e b estao em c
T arcLength(const circle& c, pt a, pt b) {
    pt d = (a-c.c)/(b-c.c); return c.r*acosl(d.x); 
}
// checar se o ponto esta dentro da circuferencia
// -1 se dentro, 0 se na borda e 1 se ta fora
int in(const circle& c, const pt& p){
    return sgn(abs(p-c.c)-c.r);
}
// condicao: c1 != c2
vpt isect(const circle& c1, const circle& c2){
    T d = abs(c1.c - c2.c), a = c1.r, b = c2.r;
    if(sgn(d) == 0){assert(a != b); return {};}
    T C = (a*a + d*d - b*b)/(2*a*d);
    if(abs(C) > 1 + eps) return {};
    T S = sqrtl(max(1 - C*C, (T)0));
    pt tmp((c2.c - c1.c)/d * a);
    return {c1.c + tmp*pt(C,S), c1.c + tmp*pt(C,-S)};
}
vpt isect(const circle& circ, const line& lin) {
    pt c = proj(circ.c,lin); 
    T sq_dist = sq(circ.r)-abs2(circ.c-c);
    if (sgn(sq_dist) < 0) return {};
    pt offset = unit(lin.q - lin.p)*sqrtl(max(sq_dist,T(0)));
    return {c+offset,c-offset};
}
T isect_area(const circle& c1, const circle& c2) { // tested in edu 2
    //Warning: use Long Double !!!! No CF dava WA só com double.
    T d = abs(c1.c-c2.c), a = c1.r, b = c2.r; 
    if (a < b) swap(a,b);
    if (d >= a+b) return 0;
    if (d <= a-b) return pi*b*b;
    
    T ca = (a*a+d*d-b*b)/(2*a*d), cb = (b*b+d*d-a*a)/(2*b*d); //lei dos cossenos
    
    ld circulo_1 = a * acosl(ca)* a;
    ld triangulo_1 = a * ca * sinl(acosl(ca)) * a;
    
    ld circulo_2 = b * acosl(cb)* b;
    ld triangulo_2 = b * cb * sinl(acosl(cb)) * b;
 
    return circulo_1 - triangulo_1 + circulo_2 - triangulo_2;
}
pt tangent(circle c, pt p, int t = 0) {
	c.r = abs(c.r); // abs needed because internal calls y.s < 0
	if (eq(c.r,0)) return c.c;
	T d = abs(p-c.c);
	pt a = pow(c.r/d,2)*(p-c.c)+c.c;
	pt b = sqrtl(d*d-c.r*c.r)/d*c.r*unit(p-c.c)*dir(pi/2); 
	return t == 0 ? a+b : a-b;
}
vector<pair<pt,pt>> external(circle c1, circle c2) { 
	vector<pair<pt,pt>> v; 
	if (c1.r == c2.r) {
		pt tmp = unit(c1.c-c2.c)*c1.r*dir(pi/2);
		v.emplace_back(c1.c+tmp,c2.c+tmp);
		v.emplace_back(c1.c-tmp,c2.c-tmp);
	} else {
		pt p = (c2.r*c1.c-c1.r*c2.c)/(c2.r-c1.r);
		for(int i=0; i<2; i++) v.emplace_back(tangent(c1,p,i),tangent(c2,p,i));
	}
	return v;
}
vector<pair<pt,pt>> internal(circle c1, circle c2) {return external({c1.c,-c1.r},c2);}
// return the minimum enclosing circle of a triangle
circle ccCenter(pt a, pt b, pt c) { 
	b -= a; c -= a;
	pt res = b*c*(conj(c)-conj(b))/(b*conj(c)-conj(b)*c);
	return {a+res,abs(res)};
}
// return the minimum enclosing circle of a set of points O(N)
circle mec(vpt ps) {
	shuffle(ps.begin(),ps.end(), rng);
	pt o = ps[0]; 
    T r = 0, EPS = 1+1e-8;
    for(int i=0; i<(int)ps.size(); i++){
        if (abs(o-ps[i]) > r*EPS) {
            o = ps[i], r = 0; // point is on MEC
            for(int j=0; j<i; j++){
                if (abs(o-ps[j]) > r*EPS) {
                    o = (ps[i]+ps[j])/2, r = abs(o-ps[i]);
                    for(int k=0; k<j; k++) if (abs(o-ps[k]) > r*EPS){
                        auto ret = ccCenter(ps[i],ps[j],ps[k]);
                        o = ret.c;
                        r = ret.r;
                    }
                }
            } 
        }
    }
	return {o,r};
}

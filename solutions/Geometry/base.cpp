const ld EPS = 1e-9;
const ld PI = acosl(-1);

using T = ll;
// using T = ld;
typedef pair<T,T> pt;
typedef pair<pt,pt> line;
typedef vector<pt> vpt;
typedef pair<pt, T> circle;

pt operator-(pt a) { return mp(-a.ft,-a.sd); }
pt &operator+=(pt &a, pt b) {
	a.ft += b.ft;  
    a.sd += b.sd;
	return a;
}
pt &operator-=(pt &a, pt b) {
	a.ft -= b.ft;
    a.sd -= b.sd;
	return a;
}
pt &operator*=(pt &a, T r) {
	a.ft *= r;
    a.sd *= r;
	return a;
}
pt &operator/=(pt &a, T r) { 
    a.ft /= r;
    a.sd /= r;
	return a;
}

pt operator+(pt a, pt b) { return a += b; }
pt operator-(pt a, pt b) { return a -= b; }
pt operator*(pt a, T r) {return a*=r;}
pt operator*(T r, pt a) {return a*=r;}
pt operator/(pt a, T r) {return a/=r;}
int sgn(T a) { return (a>EPS)-(a<-EPS); }
T sq(T a) { return a*a; }
T abs2(pt p) { return sq(p.ft)+sq(p.sd); }
ld abs(pt p) { return sqrtl(abs2(p)); }
pt unit(pt p) { return p/abs(p); }
ld arg(pt p) { return atan2(p.sd,p.ft); }
pt conj(pt p) { return mp(p.ft,-p.sd); }
pt perp(pt p) { return mp(-p.sd,p.ft); }
pt dir(T ang) { return mp(cos(ang),sin(ang)); }


pt operator*(pt a, pt b) {return pt(a.ft*b.ft-a.sd*b.sd,a.sd*b.ft+a.ft*b.sd);}

pt operator/(pt a, pt b) {return a*conj(b)/abs2(b);}

pt reflect(const pt& p, const line& l) {
	pt a = l.ft, d = l.sd-l.ft;
	return a+conj((p-a)/d)*d; }
pt foot(const pt& p, const line& l) {
	return (p+reflect(p,l))/(T)2; }

T dot(pt p1, pt p2)
{
    return p1.ft*p2.ft+p1.sd*p2.sd;
}

T dot(pt p1, pt p2, pt p3)
{
    return dot(p2-p1, p3-p1);
}

T cross(pt p1, pt p2)
{
    return p1.ft*p2.sd-p1.sd*p2.ft;
}

T cross(pt p1, pt p2, pt p3)
{
    return cross(p2-p1, p3-p1);
}

// rotate a 90 degrees centered in c
pt rotate90(pt a, pt c = mp(0,0))
{
    a-=c;
    swap(a.ft,a.sd);
    a.ft = -a.ft;
    a+=c;
    return a;
}

// rotate a d degrees centered in c
pt rotate(pt a, long double d, pt c = mp(0,0))
{
    a-=c;
    pt b;
    b.ft = a.ft*cos(d) - a.sd*sin(d);
    b.sd = a.sd*cos(d) + a.ft*sin(d); 
    b+=c;
    return b;
}

bool onseg(pt p, line l) {
	return sgn(cross(l.ft,l.sd,p)) == 0 && sgn(dot(p,l.ft,l.sd)) <= 0;}

// distance betweem a line and a point, needs two points which are in the line
ld linedist(line lin, pt at)
{
    ld rs = abs(cross(at, lin.ft, lin.sd));
    rs/=abs(lin.ft-lin.sd);
    return rs;
}

// distance betweem a segment and a point
ld point_seg(line seg, pt at)
{
    if(dot(seg.ft, at, seg.sd) <= 0)
        return abs(at-seg.ft);
    if(dot(seg.sd, at, seg.ft) <= 0)
        return abs(at-seg.sd);
    return linedist(seg, at);
}

//  Usage: vpt v; sort(all(v),angleCmp);
// used to sort points int ccw around the origin
int half(pt x) { return x.sd != 0 ? sgn(x.sd) : -sgn(x.ft); }
bool angleCmp(pt a, pt b) { int A = half(a), B = half(b);
	return A == B ? cross(a,b) > 0 : A < B; }

// equivalent to: sort(all(v),[](pt a, pt b) { 
//    return atan2(a.sd,a.ft) < atan2(b.sd,b.ft); });

// {unique intersection point} if it exists
// {b.f,b.s} if input lines are the same
// empty if lines do not intersect
vpt lineIsect(const line& a, const line& b) {
	T a0 = cross(a.ft,a.sd,b.ft), a1 = cross(a.ft,a.sd,b.sd); 
	if (a0 == a1) return a0 == 0 ? vpt{b.ft,b.sd} : vpt{};
	return {(b.sd*a0-b.ft*a1)/(a0-a1)};
}

// point in interior of both segments a and b, if it exists
vpt strictIsect(const line& a, const line& b) {
	T a0 = cross(a.ft,a.sd,b.ft), a1 = cross(a.ft,a.sd,b.sd); 
	T b0 = cross(b.ft,b.sd,a.ft), b1 = cross(b.ft,b.sd,a.sd); 
	if (sgn(a0)*sgn(a1) < 0 && sgn(b0)*sgn(b1) < 0)
		return {(b.sd*a0-b.ft*a1)/(a0-a1)};
	return {};
}

// intersection of segments, a and b may be degenerate
vpt segIsect(const line& a, const line& b) { 
	vpt v = strictIsect(a,b); if (!v.empty()) return v;
	set<pt> s;
	#define i(x,y) if (onseg(x,y)) s.insert(x)
	i(a.ft,b); i(a.sd,b); i(b.ft,a); i(b.sd,a);
	return {all(s)};
}
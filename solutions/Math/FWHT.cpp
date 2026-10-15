

void FWHT(vector<int>& a, bool inv) {
    int n = a.size();
	for (int step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) 
            rep(j,i,i+step) {
                int &u = a[j], &v = a[j + step]; 
                tie(u, v) =	inv ? mp(v - u, u) : mp(v, u + v); // AND
                // tie(u, v) = inv ? mp(v, u - v) : mp(u + v, u); // OR /// include-line
                // tie(u, v) = mp(u + v, u - v); // XOR /// include-line
            }
	}
	// if (inv) for (int& x : a) x /= n; // XOR only /// include-line
}
vector<int> multiply(vector<int> a, vector<int> b) {
	int n = 1;
    while(n < a.size())
        n<<=1;
    a.resize(n);
    b.resize(n);
    FWHT(a, 0); 
    FWHT(b, 0);
	rep(i,0,n) 
        a[i] *= b[i];
	FWHT(a, 1); 
    return a;
}

pii a[N];
// multiply alot of polinoms of the form (x^0 + x^i) / can be done in Alog(A)^2, where A is max i
// probably it will be modular
pair<vector<int>,vector<int>> Multi_FWHT(int l, int r)
{
	if(l == r)
	{
		vector<int> x(1,a[l].ft);
		vector<int> y(1,a[l].sd);
		return mp(x,y);
	}
	int mid = (l+r) >> 1;
	auto [a,c] = Multi_FWHT(l,mid);
	auto [b,d] = Multi_FWHT(mid+1,r);
	int m = r-l+1;
	vector<int> ab,bc,ad,cd;
	ab = multiply(a,b);
	bc = multiply(b,c);
	ad = multiply(a,d);
	cd = multiply(c,d);
	ab.resize(m);
	bc.resize(m);
	rep(i,0,(m)/2){
		ab[i+m/2] = cd[i];
		bc[i+m/2] = ad[i];
	}
	return mp(ab,bc);
}
const int DIG = 7;
const int BASE = 1e7; // Mude para DIG=9, BASE=1e9 se não for usar FFT

typedef vector<long long> poly;

poly mult(const poly& p, const poly& q) {
    int sz = p.size(), half = sz/2;

    if(sz <= 64) {
        poly ret(2*sz);
        for(int i = 0; i < sz; i++)
            for(int j = 0; j < sz; j++)
                ret[i+j] += p[i] * q[j];
        return ret;
    }

    poly p1(p.begin(), p.begin() + half), p2(p.begin() + half, p.end());
    poly q1(q.begin(), q.begin() + half), q2(q.begin() + half, q.end());
    poly p1p2(half), q1q2(half);
    for(int i = 0; i < half; i++)
        p1p2[i] = p1[i] + p2[i], q1q2[i] = q1[i] + q2[i];

    poly low = mult(p1, q1), high = mult(p2, q2), mid = mult(p1p2, q1q2);
    for(int i = 0; i < sz; i++)
        mid[i] -= high[i] + low[i];

    low.resize(2*sz);
    for(int i = 0; i < sz; i++)
        low[i+half] += mid[i], low[i+sz] += high[i];

    return low;
}

poly multiplicar(const poly& p, const poly& q) {
    int mx = max(p.size(), q.size());
    
    int sz = 1;
    while(sz < mx) sz *= 2;

    poly v1 = p, v2 = q;
    v1.resize(sz, 0); 
    v2.resize(sz, 0);

    return mult(v1, v2);
}

struct bigint {
    vector<int> v;
    bigint(long long x = 0) { v.push_back(x); fix(); }
    bigint(const string& s) { 
        int sign = 1, st = 0;
        while (st < s.size() && !isdigit(s[st])) if (s[st++] == '-') sign = -1;
        for (int i = s.size(); i > st; i -= DIG) {
            int l = max(st, i - DIG), val = 0;
            for (int j = l; j < i; j++) val = val * 10 + (s[j] - '0');
            v.push_back(val * sign);
        }
        fix();
    }
    bigint& fix() {
        int sign = 0;
        for (int i = 0, e = 0; i < v.size() || e; i++) {
            if (i == v.size()) v.push_back(0);
            v[i] += e; e = v[i] / BASE; v[i] %= BASE;
            if (v[i]) sign = (v[i] > 0) ? 1 : -1;
        }
        for (int i = 0; i < (int)v.size() - 1; i++) 
            if (v[i] * sign < 0) { v[i] += sign * BASE; v[i+1] -= sign; }
        while (v.size() > 1 && !v.back()) v.pop_back();
        return *this;
    }
    int cmp(const bigint& x) const {
        for (int i = max(v.size(), x.v.size()) - 1; i >= 0; i--) {
            int a = i < v.size() ? v[i] : 0, b = i < x.v.size() ? x.v[i] : 0;
            if (a != b) return a > b ? 1 : -1;
        }
        return 0;
    }
    bool operator<(const bigint& x) const { return cmp(x) < 0; }
    bool operator==(const bigint& x) const { return cmp(x) == 0; }
    bool operator!=(const bigint& x) const { return cmp(x) != 0; }
    bool operator<=(const bigint& x) const { return cmp(x) <= 0; }
    bool operator>(const bigint& x) const { return cmp(x) > 0; }
    bool operator>=(const bigint& x) const { return cmp(x) >= 0; }

    bigint operator-() const { bigint r=*this; for(int& x: r.v) x=-x; return r; }
    bigint operator+(const bigint& x) const {
        bigint r = *this; r.v.resize(max(v.size(), x.v.size()), 0);
        for(int i=0; i<x.v.size(); i++) r.v[i] += x.v[i];
        return r.fix();
    }
    bigint operator-(const bigint& x) const {
        bigint r = *this; r.v.resize(max(v.size(), x.v.size()), 0);
        for(int i=0; i<x.v.size(); i++) r.v[i] -= x.v[i];
        return r.fix();
    }
    bigint operator*(const bigint& x) const {
        poly p(v.begin(), v.end()), q(x.v.begin(), x.v.end()), res = multiplicar(p, q);
        bigint ans; ans.v.assign(res.size(), 0); long long e = 0;
        for (int i = 0; i < res.size(); i++) {
            long long val = res[i] + e; ans.v[i] = val % BASE; e = val / BASE;
        }
        while (e) { ans.v.push_back(e % BASE); e /= BASE; }
        return ans.fix(); 
    }
    bigint operator/(const bigint& x) const {
        if (x.v.empty()) return 0;
        int s1 = (v.empty() || v.back() >= 0) ? 1 : -1, s2 = (x.v.empty() || x.v.back() >= 0) ? 1 : -1;
        bigint A = s1 == -1 ? -*this : *this, B = s2 == -1 ? -x : x;
        if (A < B) return 0;
        
        bigint q; int m = B.v.size();
        q.v.assign(max(0, (int)A.v.size() - m + 1), 0);
        vector<long long> rem(A.v.begin(), A.v.end());
        rem.push_back(0); 
        
        long long d = B.v.back() * 1LL * BASE + (m > 1 ? B.v[m-2] : 0);
        
        for (int i = q.v.size() - 1; i >= 0; i--) {
            int j = m + i - 1;
            q.v[i] = (int)((((__int128)rem[j] * BASE) + (j > 0 ? rem[j-1] : 0)) / d);
            long long carry = 0;
            
            for (int k = 0; k < m || carry; k++) { 
                if (i+k >= rem.size()) rem.push_back(0);
                
                long long cur = rem[i+k] - (k < m ? B.v[k] : 0) * 1LL * q.v[i] + carry;
                if ((rem[i+k] = (cur % BASE)) < 0) { rem[i+k] += BASE; cur -= BASE; }
                carry = cur / BASE;
            }
            if (!i || !j) break;
            
            rem[j-1] += rem[j] * 1LL * BASE; rem[j] = 0; 
        }
        
        q.fix(); return (s1 != s2 && !(q.v.size() == 1 && q.v[0] == 0)) ? -q : q;
    }
    bigint operator%(const bigint& x) const { return *this - (*this / x) * x; }
    
    bigint& operator+=(const bigint& x) { return *this = *this + x; }
    bigint& operator-=(const bigint& x) { return *this = *this - x; }
    bigint& operator*=(const bigint& x) { return *this = *this * x; }
    bigint& operator/=(const bigint& x) { return *this = *this / x; }
    bigint& operator%=(const bigint& x) { return *this = *this % x; }

    friend ostream& operator<<(ostream& o, const bigint& x) {
        if (x.v.empty()) return o << 0;
        o << x.v.back();
        for (int i = (int)x.v.size() - 2; i >= 0; i--) 
            o << setw(DIG) << setfill('0') << abs(x.v[i]);
        return o;
    }
};
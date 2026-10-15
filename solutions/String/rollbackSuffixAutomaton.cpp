#include<bits/stdc++.h>
using namespace std;
//template
#pragma region
 
// #include <ext/pb_ds/assoc_container.hpp> // Common file
// #include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
// using namespace __gnu_pbds;
// #pragma GCC optimize("O3", "unroll-loops") // for fast N^2
// #pragma GCC target("avx2", "popcnt") // for fast popcount
// #pragma GCC optimize("Ofast", "avx2") // cheating TLE
// some macros
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define mt make_tuple
#define mp make_pair
#define eb emplace_back
#define pb push_back
// loop that goes (begin,..,end]
// #define rep(i, begin, end) for (__typeof(begin) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define rep(i, begin, end) for(int i = begin; i < end; i++)
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef pair<double,double> pdb;
 
// template<class T> using ordset = tree<
// T,
// null_type,
// less<T>,
// rb_tree_tag,
// tree_order_statistics_node_update>;
//read and print pair
template<typename T>
ostream& operator<<(ostream& os, pair<T, T> p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template<typename T>
istream& operator>>(istream& is, pair<T, T> &p) {
    is >> p.first >> p.second;
    return is;
}
 

 
 
 
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion


const int N = 200100;
struct state {
    int len, link = 0;
    map<char, int> next;
    vector<int> reach;
};

struct roll {
    int id;
    int link;
    int u,v;
    char c;
    roll(int id, int u, int v, char c): id(id), link(0), u(u), v(v), c(c) {}; //memo next
    roll(int id, int u, int v): id(id), link(1), u(u), v(v) {}; //memo link
};
state st[N * 2];
// old edges from state
stack<roll> added;
// node added and possible clone added
stack<pii> bad;
// last used in extend
stack<int> lst;
int sz, last;
void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}


void sa_extend(char c) {
    pii at;
    int cur = sz++;
    bad.emplace(cur,-1);
    at.ft = cur;
    at.sd = -1;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next[c]) {
        added.emplace(cur, p, st[p].next[c], c);
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            // do something
            added.emplace(cur, cur, st[cur].link);
            st[cur].link = q;
        } else {
            int clone = sz++;
            at.sd = clone;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            added.emplace(cur, clone, st[clone].link);
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                added.emplace(cur, p, st[p].next[c], c);
                st[p].next[c] = clone;
                p = st[p].link;
            }
            added.emplace(cur, q, st[q].link);  
            added.emplace(cur, cur, st[cur].link);       
            int old = st[q].link;
            // do something
            st[q].link = st[cur].link = clone;
            bad.top().sd = clone;
        }
    }
    lst.push(last);
    last = cur;
}

void rollback()
{
    int id = added.top().id;
    while(!added.empty() && id == added.top().id)
    {
        auto at = added.top();
        if(at.link)
        {
            int old = st[at.u].link;
            // do something
            st[at.u].link = at.v;
        }else
        {
            st[at.u].next[at.c] = at.v;
        }
        added.pop();
    }

    last = lst.top();
    lst.pop();
    bad.pop();
}

int main(){
    return 0;
}
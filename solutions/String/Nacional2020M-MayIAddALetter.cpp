#include<bits/stdc++.h>
using namespace std;

//template

const int N = 200100;
struct state {
    int len, link = 0, qt = 0;
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
ll rs = 0, tot = 0;
state st[N * 2];
stack<roll> added;
stack<pii> bad;
stack<int> lst;
int sz, last;
void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}

ll solve(int at)
{
    return st[at].len - st[st[at].link].len;
}

void sa_extend(char c) {
    pii at;
    int cur = sz++;
    bad.emplace(cur,-1);
    at.ft = cur;
    at.sd = -1;
    st[cur].len = st[last].len + 1;
    st[cur].qt = 0;
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
            st[q].qt++;
            if(q != 0 && st[q].qt == 1)
            {
                rs -= solve(q);
            }
            added.emplace(cur, cur, st[cur].link);
            st[cur].link = q;
        } else {
            int clone = sz++;
            at.sd = clone;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            added.emplace(cur, clone, st[clone].link);
            st[st[q].link].qt++;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                added.emplace(cur, p, st[p].next[c], c);
                st[p].next[c] = clone;
                p = st[p].link;
            }
            added.emplace(cur, q, st[q].link);  
            added.emplace(cur, cur, st[cur].link);       
            int old = st[q].link;
            st[st[q].link].qt--;
            tot -= solve(q);
            if(st[q].qt == 0)
                rs -= solve(q);
            st[q].link = st[cur].link = clone;
            if(st[q].qt == 0)
                rs += solve(q);
            tot += solve(q);
            tot += solve(clone);
            st[clone].qt = 2;
            bad.top().sd = clone;
        }
    }
    rs += solve(cur);
    tot += solve(cur);
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
            tot -= solve(at.u);
            if(at.u !=0 && st[at.u].qt == 0)
                rs -= solve(at.u);
            int old = st[at.u].link;
            st[old].qt--;
            if(old != 0 && st[old].qt == 0)
            {
                rs += solve(old);
            }
            st[at.u].link = at.v;
            st[at.v].qt++;
            if(at.v != 0 && st[at.v].qt == 1)
            {
                rs -= solve(at.v);
            }
            if(at.u !=0 && st[at.u].qt == 0)
                rs += solve(at.u);
            tot += solve(at.u);
        }else
        {
            st[at.u].next[at.c] = at.v;
        }
        added.pop();
    }
    rs -= solve(bad.top().ft);
    tot -= solve(bad.top().ft);
    if(bad.top().sd != -1){
        rs -= solve(bad.top().sd);
        tot -= solve(bad.top().sd);
    }
    last = lst.top();
    lst.pop();
    bad.pop();
}

void test()
{
    string s;
    cin >> s;
    sa_init();
    for(char ch:s)
    {
        sa_extend(ch);
    }   
    cout << tot -  rs << '\n';
    cin >> s;
    for(char ch:s)
    {
        if(ch == '-'){
            
            rollback();
        }   
        else{
            sa_extend(ch);
        }
        cout << tot - rs << '\n';
    }   
}   

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while(t--)
        test();
    return 0;
}
// ABC
// 5
// 3 3 3 2 5

// l -1^k r
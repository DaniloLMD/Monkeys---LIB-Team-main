#include<bits/stdc++.h>
using namespace std;
//template

vector<pii> edges;
int n;

void random_tree()
{
    rep(i, 1, n)
        edges.eb(i,rng()%i);
}
void catter()
{
    int k = rng()%(n/2) + n/2;
    rep(i, 1, k)
        edges.eb(i-1,i);
    rep(i, k, n)
        edges.eb(rng()%(i),i);
}

void star()
{
    rep(i, 1, n)
        edges.eb(0,i);
}

void print_tree()
{
    vector<int> p;
    rep(i, 1, n+1)
        p.pb(i);
    shuffle(all(p),rng);
    shuffle(all(edges),rng);
    cout << n << '\n';
    for(auto [u,v]:edges)
        cout << p[u] << ' ' << p[v] << '\n';
}
 
int32_t main(int argc, char *argv[])
{
    n = stoi(argv[1]);
    int tp = stoi(argv[2]);
    if(!tp)
        star();
    else
    {
        if(tp%3 == 0)
            catter();
        else
            random_tree();
    }
    print_tree();
    return 0;
}
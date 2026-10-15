#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define pb push_back

const int N = 30010;

int a[N];
vector<int> tree[N << 2];

void build(int x, int tl, int tr){
    if(tl == tr){
        tree[x].pb(a[tl]);
    }
    else{
        int tm = tl + tr >> 1;
        build(lef(x), tl, tm);
        build(rig(x), tm+1, tr);
        tree[x].resize(tr-tl+1);
        merge(all(tree[lef(x)]), all(tree[rig(x)]), tree[x].begin());
    }
}

int get(int x, int tl, int tr, int l, int r, int k){
    if(tl > r || tr < l)
        return 0;
    else if(tl >= l && tr <= r)
        return (int)tree[x].size() - (upper_bound(all(tree[x]), k) - tree[x].begin());
    else{
        int tm = tl + tr >> 1;
        return get(lef(x),tl,tm,l,r,k) + get(rig(x),tm+1,tr,l,r,k);
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>a[i];
    }

    build(1,1,n);

    int q; cin >> q;
    while(q--){
        int l, r, x;
        cin >> l >> r >> x;
        cout<<get(1,1,n,l,r,x)<<"\n";
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

#pragma region 
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

// #pragma GCC optimize("Ofast") // for fast N^2
// #pragma GCC target("avx2") // for fast N^2
// #pragma GCC target("popcnt") // for fast popcount

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define get_bit(x,i) ((x)&(1ll<<(i)))
#define dbg(x) cout<<#x<<" = " <<x<<endl;

// Template do felipe - tem umas coisas na lib q usa vc<T> e  vvc<T>.
template<class T> using vc = vector<T>;
template<class T> using vvc = vector<vc<T>>;

using ll = long long int; 
using ld = long double;
using i28 = __int128_t;
using vi = vector<int>;
using vl = vector<ll>; 
template<class T> using ordset = tree<T,null_type, less<T>,
rb_tree_tag, tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion

void test() {

}   
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t_ = 1;
    // cin >> t_;
    while(t_--) test();
    
    return 0;
}

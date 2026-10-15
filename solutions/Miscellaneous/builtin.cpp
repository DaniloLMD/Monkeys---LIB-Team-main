#include<bits/stdc++.h>
using namespace std;

int main()
{
    int x = 1021;
    cout << __builtin_popcount(x) << '\n';
    cout << __builtin_clz(x) << '\n';
    cout << __builtin_ctz(x) << '\n';
    cout << __builtin_parity(x) << '\n';
    ll lx = 1021;
    cout << __builtin_popcountll(lx) << '\n';
    cout << __builtin_clzll(lx) << '\n';
    cout << __builtin_ctzll(lx) << '\n';
    cout << __builtin_parityll(lx) << '\n';
}
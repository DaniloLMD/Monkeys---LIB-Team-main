#include<bits/stdc++.h>
using namespace std;
//template

int main(int argc, char *argv[]) {
    int n = stoi(argv[1]);
    int lim = stoi(argv[2]);
    cout << n << '\n';
    rep(i, 0, n)
        cout << (rng()%lim) << ' ';
    cout << '\n';
    return 0;
}
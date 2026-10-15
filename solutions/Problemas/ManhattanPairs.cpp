#include <bits/stdc++.h>
using namespace std;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> pt(n<<1);
    for(int i=0; i<(n<<1); i++) cin >> pt[i].first >> pt[i].second;
    vector<pair<int,int>> X,Y;
    for(int i=0; i<(n<<1); i++) 
        X.emplace_back(pt[i].first,i),Y.emplace_back(pt[i].second,i);
    sort(X.begin(),X.end()), sort(Y.begin(),Y.end());
    vector<int> A,B,C,D;
    for(int i=0; i<(n<<1); i++){
        auto [x,id] = X[i];
        int y = pt[id].second;
        int j = lower_bound(Y.begin(),Y.end(),{y,id}) - Y.begin();
        if(i < n && j < n) A.push_back(id);
        else if(i >= n && j >= n) B.push_back(id);
        else if(i < n && j >= n) C.push_back(id);
        else D.push_back(id);
    }
    for(int i=0; i<A.size(); i++) cout << A[i] << ' ' << B[i] << '\n';
    for(int i=0; i<C.size(); i++) cout << C[i] << ' ' << D[i] << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int karmakarp(multiset<int>& items, multiset<int>& P1, multiset<int>& P2){

    if (items.size() == 1){
        P1.clear();
        P1.insert(*items.begin());
        P2.clear();
        return *items.begin();
    }

    int bigger1 = *items.rbegin();
    items.erase(items.find(*items.rbegin()));
    int bigger2 = *items.rbegin();
    items.erase(items.find(*items.rbegin()));

    int diff = bigger1 - bigger2;
    items.insert(diff);

    int bestDiff = karmakarp(items, P1, P2);

    if (P1.find(diff) == P1.end()){
        swap(P1, P2);
    }

    P1.erase(P1.find(diff));
    P1.insert(bigger1);

    P2.insert(bigger2);
    return bestDiff;
}

int main(){

    vector<int> vet = {3, 8, 12, 16, 38, 41, 73};
    multiset<int> P1, P2;

    multiset<int> items;
    for (int v : vet)
        items.insert(v);

    cout << karmakarp(items, P1, P2) << "\n";

    for (int v : P1)
        cout << v << " ";
    cout << "\n";

    for (int v : P2)
        cout << v << " ";
    cout << "\n";

    return 0;
}
#include<bits/stdc++.h>

using namespace std;

int32_t main(){
    srand(252);
    vector<string> vt = {
        "Nollyad",
        "Faslecar",
        "Nopebi Lifesa",
        "Laelovatsug",
        "Atak Kichan",
        "Alunea",
        "Lesin",
        "Nhotivew"
    };
    random_shuffle(vt.begin(),vt.end());
    for(auto s:vt)
        cout << "\\item " << s << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main(){
	string s = "abaab";
	int cont = 0;
	sort(s.begin(), s.end()); // para todas as permutacoes
	do{
		cont++;
		cout << s << endl;
	}while(next_permutation(s.begin(), s.end()));
	cout << cont << endl;
	return 0;
}
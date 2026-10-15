//istringstream
//ler linhas do tipo: +0 +2 -0 +1 -1 -2
string s;
istringstream iss;
rep(i, 0, n){
    getline(cin, s);
    iss.clear();
    iss.str(s);

    while(iss >> ch){
        iss >> in;
    }
}

//ostringstream
ostringstream oss;

int idade1 = 30;
string nome1 = "Alice";
double salario1 = 2500.75;
oss << "Relatório 1\n";
oss << "Nome: " << nome1 << ", Idade: " << idade1 << ", Salário: R$ " << salario1 << "\n";
cout << oss.str() << endl;

oss.str("");
oss.clear();

int idade2 = 45;
string nome2 = "Bob";
double salario2 = 3200.50;
oss << "Relatório 2\n";
oss << "Nome: " << nome2 << ", Idade: " << idade2 << ", Salário: R$ " << salario2 << "\n";
cout << oss.str() << endl;
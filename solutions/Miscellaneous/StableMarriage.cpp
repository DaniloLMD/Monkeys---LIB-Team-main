const int MAXN = 510;

queue<int> menPref[MAXN], Q;
int womenPref[MAXN][MAXN];//womenPref[a][b] = c, men b is the c-th preference of women a
int womenMarryWith[MAXN];

void test()
{   
    int n, in;
    int men, women, other;
    cin >> n;
    rep(i, 0, n)
        womenMarryWith[i] = -1;

    rep(i, 0, n){
        cin >> men;
        men--;
        rep(j, 0, n){
            cin >> in;
            in--;
            menPref[men].push(in);
        }
    }
    rep(i, 0, n){
        cin >> women;
        women--;
        rep(j, 0, n){
            cin >> in;
            in--;
            womenPref[women][in] = j;
        }
    }

    rep(i, 0, n){
        Q.push(i);
    }

    while(!Q.empty()){
        men = Q.front();
        Q.pop();

        if (menPref[men].empty())
            continue;

        women = menPref[men].front();
        menPref[men].pop();

        if (womenMarryWith[women] == -1){
            womenMarryWith[women] = men;
        }
        else if (womenPref[women][womenMarryWith[women]] > womenPref[women][men]){
            other = womenMarryWith[women];
            womenMarryWith[women] = men;
            Q.push(other);
        }
        else{
            Q.push(men);
        }
    }

    rep(i, 0, n){
        cout << i+1 << "  " << womenMarryWith[i]+1 << "\n";
    }

    rep(i, 0, n){
        while(!menPref[i].empty())
            menPref[i].pop();
    }
}   
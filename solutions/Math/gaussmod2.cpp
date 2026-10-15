//https://www.spoj.com/problems/DFLOOR/en/
#include <bits/stdc++.h>

using namespace std;

const int N = 300;

int gauss(vector< bitset< N > > a, int n, int m, bitset< N > &ans){
    vector< int > where(m, -1);
    for(int col = 0, row = 0 ; col < m && row < n ; ++col){
        for(int i = row ; i < n ; ++i){
            if(a[i][col]){
                swap(a[i], a[row]);
                break;
            }
        }

        if(!a[row][col]){
            continue;
        }

        where[col] = row;

        for(int i = 0 ; i < n ; i++){
            if(i != row && a[i][col]){
                a[i] ^= a[row];
            }
        }

        ++row;
    }

    for(int i = 0 ; i < m ; i++){
        if(where[i] != -1){
            ans[i] = a[where[i]][m];
        }
    }

    // cout << " ------- \n";
    // for(auto u: a){
    //     cout << u << "\n";
    // } 

    for(int i = 0 ; i < n ; i++){
        int sum = 0;
        for(int j = 0 ; j < m ; j++){
            sum += ans[j] * a[i][j];
        }

        if((sum % 2) != a[i][m]){
            return 0;
        }
    }

    return 1;
}

char tab[20][20];
int vi[4] = {0, 0, 1, -1};
int vj[4] = {1, -1, 0, 0};
int x, y;

bool ok(int a, int b){
    return 0 <= a && a < x && 0 <= b && b < y;
}

int main(){
    while(scanf("%d %d", &x, &y) != EOF){
        if(x == 0 && y == 0){
            break;
        }
        
        swap(x, y);

        for(int i = 0 ; i < x ; i++){
            for(int j = 0 ; j < y ; j++){
                scanf("\n%c", &tab[i][j]);
            }
        }

        vector< bitset< N > > q;

        for(int i = 0 ; i < x ; i++){
            for(int j = 0 ; j < y ; j++){
                bitset< N > v;

                for(int k = 0 ; k < 4 ; k++){
                    int xi = vi[k] + i;
                    int xj = vj[k] + j;

                    if(ok(xi, xj)){
                        v[xi * y + xj] = 1;
                    }
                }

                v[i * y + j] = 1;
                v[x * y] = !(tab[i][j] - '0');
                q.push_back(v);
                // cout << v << "\n";
            }
        }

        bitset< N > ans;
        if(gauss(q, q.size(), x * y, ans)){
            vector< int > ians;
            for(int i = 0 ; i < x * y ; i++){
                if(ans[i]){
                    ians.push_back(i);                    
                }
            }

            printf("%lu\n", ians.size());

            for(auto u: ians){
                printf("%d %d\n", (u % y) + 1, (u / y) + 1);
            }
        }else{
            printf("-1\n");
        }
    }

    return 0;
}
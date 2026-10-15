//UVALive - 6072
//http://adilet.org/blog/palindromic-tree/
#include <bits/stdc++.h>
using namespace std;

const int N=200010;
typedef long long ll;

struct node {
    int next[26];
    int len;
    int sufflink;
    int num;
    int lazy;
};

string s;
node tree[N]; 
int num;            // node 1 - root with len -1, node 2 - root with len 0
int suff;           // max suffix palindrome

bool addLetter(int pos) {
    int cur = suff, curlen = 0;
    int let = s[pos] - 'a';

    while (true) {
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])     
            break;  
        cur = tree[cur].sufflink;
    }       
    if (tree[cur].next[let]) {  
        suff = tree[cur].next[let];
        tree[suff].lazy++;
        return false;
    }

    num++;
    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[cur].next[let] = num;
    tree[num].lazy=1;
    // cout<<num<<" "<<let<<"\n";
    if (tree[num].len == 1) {
        tree[num].sufflink = 2;
        tree[num].num = 1;
        return true;
    }

    while (true) {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
            tree[num].sufflink = tree[cur].next[let];
            break;
        }       
    }           

    tree[num].num = 1 + tree[tree[num].sufflink].num;

    return true;
}

void initTree() {
    num = 2; suff = 2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len = 0; tree[2].sufflink = 1;
}
ll value[26],pot[N];
vector<pair<ll,ll>> pl;
const ll mod=777777777LL;
void dfs(int t)
{
    for (int i = 0; i < 26; ++i)
    {
        // cout<<t<<" "<<tree[t].next[i]<<'\n';
        if(tree[t].next[i])
        {
            dfs(tree[t].next[i]);
        }
    }   
}
void dfs1(int t,ll at,int pt)
{
    // cout<<t<<' '<<at<<" "<<tree[t].lazy<<'\n';
    if(t>2)
        pl.push_back({at,tree[t].lazy});
    for (int i = 0; i < 26; ++i)
    {
        if(tree[t].next[i])
        {
            // cout<<t<<" --- "<<(char)(i+'a')<<" --> "<<tree[t].next[i]<<"\n";
            dfs1(tree[t].next[i],(at+value[i]*pot[pt])%mod,pt+1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    pot[0]=1;
    for (int i = 1; i < N; ++i)
    {
        pot[i] = (pot[i-1]*26LL)%mod;
    }
    int q;
    cin>>q;
    while(q--)
    {

        int n,m;
        cin>>n>>m;
        cin>>s;

        initTree();

        for (int i = 0; i < n; i++) {
            addLetter(i);
        }
        for (int i = num; i >0 ; --i)
        {
            if(tree[i].sufflink)
                tree[tree[i].sufflink].lazy+=tree[i].lazy;
        }
        // cout<<num<<" "<<s<<'\n';
        // dfs(1);
        for (int i = 0; i < m; ++i)
        {
            ll k;
            cin>>k;
            for (int j = 0; j < 26; ++j)
            {
                cin>>value[j];
                value[j]%=mod;
            }
            pl.clear();
            dfs1(1,0,0);
            dfs1(2,0,0);
            sort(pl.begin(),pl.end());
            ll now=0;
            int j=0;
            while(j<pl.size() && now+pl[j].second<k)
            {
                now+=pl[j++].second;
            }
            cout<<pl[j].first<<"\n";
        }
        cout<<"\n";
        for (int i = 0; i <= num; ++i)
        {
            tree[i].len=tree[i].sufflink=tree[i].num=tree[i].lazy=0;
            for (int j = 0; j < 26; ++j)
            {
                tree[i].next[j]=0;
            }
        }
    }

    return 0;
}
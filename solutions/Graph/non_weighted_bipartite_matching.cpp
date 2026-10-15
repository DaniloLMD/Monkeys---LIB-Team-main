#include<bits/stdc++.h>
using namespace std;

#define MAX_V1 1000000
#define MAX_V2 1000000
#define MAX_E 8000000

int V1 = 0,V2 = 0,l[MAX_V2],r[MAX_V1];
int E,to[MAX_E],nex[MAX_E],last[MAX_V1];

void hk_init(){
    memset(last,-1,sizeof last);
    E=0;
}

void hk_add_edge(int u, int v){
    to[E] = v; nex[E] = last[u]; last[u] = E++;
}

bool visited[MAX_V1];

bool hk_dfs(int u){
    if(visited[u]) return false;
    visited[u] = true;
    
    for(int e = last[u],v;e != -1;e = nex[e]){
        v = to[e];
        
        if(l[v] == -1 || hk_dfs(l[v])){
            r[u] = v;
            l[v] = u;
            return true;
        }
    }
    
    return false;
}

int hk_match(){
    memset(l,-1,sizeof l);
    memset(r,-1,sizeof r);
    bool change = true;
    
    while(change){
        change = false;
        memset(visited,false,sizeof visited);
        
        for(int i = 0;i < V1;++i)
            if(r[i] == -1)
                change |= hk_dfs(i);
    }
    
    int ret = 0;
    
    for(int i = 0;i < V1;++i)
        if(r[i] != -1) ++ret;
    
    return ret;
}

int n,m;	
bool valid(int x, int y)
{
	return (x > 0  && x <= n && y > 0 && y <= m);
}
int id[1005][1005];
int dx[] = {-1,-1,1,1,2,2,-2,-2};
int dy[] = {-2,2,-2,2,-1,1,-1,1};
int main()
{
    int e;
 	scanf("%d %d %d",&V1,&V2,&e);
 	hk_init();
 	for (int i = 0; i < e; ++i)
    {
        int a,b;
        cin>>a>>b;
        hk_add_edge(a,b);
    }
	
	printf("%d\n",hk_match());
    for (int i = 0; i < V1; ++i)
    {
        if(r[i]!=-1)
            cout<<i<<' '<<r[i]<<"\n";
    }
  return 0;
}
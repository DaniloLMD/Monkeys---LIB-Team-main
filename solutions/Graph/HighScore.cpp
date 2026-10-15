#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;
const int N = 3100;
const int M = 5100;
const ll inf = -1e16;
 
pair<pii,ll> edges[M];
ll dist[N];
int mark[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin>>n>>m;
    for (int i = 1; i <= n; ++i)
    {
        dist[i] = inf;
    }
    for (int i = 0; i < m; ++i)
    {
        int a,b;
        cin>>a>>b>>edges[i].second;
        edges[i].first = {a,b};
    }
    dist[1] = 0;
    mark[1] = 0;
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j < m ; ++j)
        {
            int a,b;
            tie(a,b) = edges[j].first;
            if(dist[a] > inf)
            {
                if(dist[b] < dist[a] + edges[j].second)
                {
                    mark[b] = i;
                    dist[b] = dist[a] + edges[j].second;   
                }
            }
        }
    }
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j < m ; ++j)
        {
            int a,b;
            tie(a,b) = edges[j].first;
            mark[b] = max(mark[b],mark[a]);
        }
    }
    if(mark[n]==n)
        cout<<"-1\n";
    else
        cout<<dist[n]<<"\n";
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
//template
const int N = 50100;
const int K = 250;

//DSU with Rollback

vector<pii> ed;
namespace mo
{
    struct query
    {
        int idx, l, r;
    };
    vector<query> queries;
    vector<int> ans;

    bool cmp(query x, query y)
    {
        if (x.l / K != y.l / K)
            return x.l / K < y.l / K;
        return x.r < y.r;
    }
    void run(int n)
    {
		dsu::init(n);
        sort(queries.begin(), queries.end(), cmp);
        ans.resize(queries.size());
        int lim, cr;
        int check, at = -1;
        for (int i = 0; i < queries.size(); i++)
        {
			int al = queries[i].l;
			int ar = queries[i].r;
			if(al/K != at)
			{
				while(dsu::cs)
					dsu::roll_back();
				at = al/K;	
				lim = min<int>(at*K + K-1,ed.size()-1);
				cr = lim;
			}
			if(ar/K == at)
			{
				check = 0;
				rep(j, al, ar+1)
					dsu::merge(ed[j].ft,ed[j].sd);
			}else
			{
				while(cr < ar)
				{
					cr++;
					dsu::merge(ed[cr].ft,ed[cr].sd);
				}
				check = dsu::cs;
				rep(j, al,lim+1)
					dsu::merge(ed[j].ft,ed[j].sd);

			}
            ans[queries[i].idx] = n-dsu::cs;
			while(dsu::cs != check)
				dsu::roll_back();
        }
    }
}


void test()
{
	int n, m;
	cin >> n >> m;
	rep(i, 0, m)
	{
		int u, v;
		cin >> u >> v;
		ed.eb(u,v);
	}
	int k;
	cin >> k;
	rep(i, 0, k)
	{
		mo::query curr;
		cin >> curr.l >> curr.r;
		curr.l--;
		curr.r--;
		curr.idx = i;
		mo::queries.pb(curr);
	}
	mo::run(n);
	rep(i, 0, k)
		cout << mo::ans[i] << '\n';
}   


int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int t = 1;
	// cin >> t;
	while(t--)
		test();
	return 0;
}


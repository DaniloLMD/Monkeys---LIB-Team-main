#include<bits/stdc++.h>
using namespace std;
//template
const int N = 300100;
//DSU with Rollback
map<pii,int> id;
struct query
{
	int l, r, u, v;
};
int ans[N], n;

vector<query> queries;
int sum = 0;
// vector<pair<pii,vector<int>>>
void solve(vector<int> &nw, int l, int r)
{
	if(l > r)
		return;
	// sum++;
	int check = dsu::cs;
	if(l == r)
	{
		// cout << l << ' ' << r << "<<<\n";

		for(int i:nw)
			dsu::merge(queries[i].u,queries[i].v);
		ans[l] = n-dsu::cs;
		
	}else
	{
		int mid = (l+r) >> 1;
		vector<int> lef,rig;
		// cout << l << ' ' << r << "<<<\n";
		for(int i:nw)
		{
			if(queries[i].l <=l && queries[i].r >= r){	
				// cout << queries[i].l << ' ' << queries[i].r << ' ' << queries[i].u << ' ' << queries[i].v << '\n';
				dsu::merge(queries[i].u,queries[i].v);
			}
			else {
				if(queries[i].l <= mid && queries[i].r >= l)
					lef.pb(i);
				if(queries[i].r > mid && queries[i].l <= r)
					rig.pb(i);
			}
		}
		// nw.clear();
		solve(lef,l,mid);
		solve(rig,mid+1,r);
	}
	while(dsu::cs != check)
			dsu::roll_back();
}
vector<int> nw;
void test()
{
	int m;
	cin >> n >> m;
	dsu::init(n);
	int pass = 1;
	rep(i, 1, m+1)
	{
		char ch;
		cin >> ch;
		if(ch == '?')
		{	
			pass++;
		}else if(ch == '+')
		{
			int u, v;
			cin >> u >> v;
			if(u > v)
				swap(u,v);
			id[mp(u,v)] = pass;
		}else
		{
			query at;
			cin >> at.u >> at.v;
			if(at.u > at.v)
				swap(at.u,at.v);
			at.l = id[mp(at.u,at.v)];
			at.r = pass-1;
			id[mp(at.u,at.v)] = 0;
			if(at.l <= at.r)
			{
				nw.pb(queries.size());
				queries.pb(at);
			}
		}
	}
	for(auto [ed,x]:id)
	{
		if(!x)
			continue;
		query at;
		at.u = ed.ft;
		at.v = ed.sd;
		at.l = x;
		at.r = pass-1;
		if(at.l <= at.r)
		{
			nw.pb(queries.size());
			queries.pb(at);
		}
	}
	// for(auto at:queries)
	// 	cout << at.l << ' ' << at.r << ' ' << at.u << ' ' << at.v << '\n';
	solve(nw,1,pass-1);
	rep(i, 1, pass)
		if(ans[i] != 0)
			cout << ans[i] << '\n';

	// cout << sum << "<<\n";
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



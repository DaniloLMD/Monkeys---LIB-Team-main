
int pai[N];
vector<int> rk[N];

int findx(int x)
{
	if(pai[x] == x)
		return x;
	return findx(pai[x]);
}
int cs = 0;
vector<pii> rmv;
void merge(int a, int b)
{
	a = findx(a);
	b = findx(b);
	if(a != b)
	{
		if(rk[a].back() < rk[b].back())
			swap(a,b);
		rk[a].pb(max(rk[a].back(),rk[b].back()+1));
		pai[b] = a;
		rmv.eb(a,b);
        cs++;
	}
}

void roll_back()
{
	pai[rmv.back().sd] = rmv.back().sd;
	rk[rmv.back().ft].pop_back();
	rmv.pop_back();
	cs--;
}
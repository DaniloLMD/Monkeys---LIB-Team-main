int pai[N];
int rk[N];
int tmp[N];

int findx(int x, int t)
{
	if(tmp[x] > t || tmp[x] == 0)
		return x;
	return findx(pai[x],t);
}
int cs = 0;
void merge(int a, int b)
{
	a = findx(a,cs);
	b = findx(b,cs);
	if(a != b)
	{
		if(rk[a] < rk[b])
			swap(a,b);
		rk[a] = max(rk[a],rk[b]+1);
		pai[b] = a;
		tmp[b] = ++cs;
		tmp[a] = 0;
	}
}
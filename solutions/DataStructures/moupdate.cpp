const int N = 100005
int n, q;
int v[N];
int vv[N];

namespace mo
{
  struct query
  {
    int idx, l, r, t;
  };
  struct update
  {
    int i, prevx, x;
  };

  int block;
  vector<query> queries;
  vector<update> updates;
  vector<int> ans;

  bool cmp(query x, query y)
  {
    if (x.l / block != y.l / block)
      return x.l / block < y.l / block;
    if (x.r / block != y.r / block)
      return x.r / block < y.r / block;
    return x.t < y.t;
  }
  void run()
  {
    block = 3153; // (2 * n) ^ 0.666
    sort(queries.begin(), queries.end(), cmp);
    ans.resize(queries.size());
    int cl = 0, cr = -1, sum = 0, t = 0;
    auto add = [&](int x)
    {
      sum += x;
    };
    auto rem = [&](int x)
    {
      sum -= x;
    };
    for (int i = 0; i < queries.size(); i++)
    {
      while (cl > queries[i].l)
      {
        cl--;
        add(v[cl]);
      }
      while (cr < queries[i].r)
      {
        cr++;
        add(v[cr]);
      }
      while (cl < queries[i].l)
      {
        rem(v[cl]);
        cl++;
      }
      while (cr > queries[i].r)
      {
        rem(v[cr]);
        cr--;
      }
      while (t > queries[i].t)
      {
        t--;
        if (queries[i].l <= updates[t].i && queries[i].r >= updates[t].i)
        {
          rem(updates[t].x);
          add(updates[t].prevx);
        }
        v[updates[t].i] = updates[t].prevx;
      }
      while (t < queries[i].t)
      {
        if (queries[i].l <= updates[t].i && queries[i].r >= updates[t].i)
        {
          rem(updates[t].prevx);
          add(updates[t].x);
        }
        v[updates[t].i] = updates[t].x;
        t++;
      }
      ans[queries[i].idx] = sum;
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    vv[i] = v[i];
  }
  for (int i = 0; i < q; i++)
  {
    int type;
    cin >> type;
    if (type == 1)
    {
      mo::update curr;
      cin >> curr.i >> curr.x;
      curr.prevx = vv[curr.i];
      vv[curr.i] = curr.x;
      mo::updates.pb(curr);
    }
    else
    {
      mo::query curr;
      cin >> curr.l >> curr.r;
      curr.r--;
      curr.idx = mo::queries.size();
      curr.t = mo::updates.size();
      mo::queries.pb(curr);
    }
  }
  mo::run();
  for (auto const &i : mo::ans)
    cout << i << endl;
}
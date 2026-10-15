struct Event {
	int type, id;
	pll pt;
};
const int N = 2010;

ll x0[N], x1[N], y[N];
int n;
pll origin;
// Cross product
ll cross(pll a, pll b) {
	return (a.sd - origin.sd) * (b.ft - origin.ft) -
	       (a.ft - origin.ft) * (b.sd - origin.sd);
}

// Which half of the plane some point lies in
int half(pll p) {
	return (p.sd < origin.sd) - (p.sd > origin.sd);
}

// Custom comparator to sort by bearing
bool operator<(Event a, Event b) {
    ll c = cross(a.pt, b.pt);
    if (c == 0) return a.type > b.type;
    return c > 0;
}

ll solve(ll mx, ll mt){
    origin = mp(mx,mt);
    vector< Event > v1, v2;

    for(int i = 0 ; i < n ; i++){
        if(y[i] == mt){
            continue;
        }

        ll x00 = x0[i];
        ll x11 = x1[i];

        if(cross(mp(x00,y[i]),mp(x11,y[i])) < 0)
            swap(x00,x11);
        if(half(mp(x00,y[i])) == 1)
        {
            v1.push_back(Event{1,i,mp(x00,y[i])});
            
            v1.push_back(Event{-1,i,mp(x11,y[i])});
        }else
        {
            v2.push_back(Event{1,i,mp(x00,y[i])});
            
            v2.push_back(Event{-1,i,mp(x11,y[i])});
        }

    }

    sort(v1.begin(), v1.end());
    
    sort(v2.begin(), v2.end());

    ll ans = 0LL;
    ll tmp = 0LL;
    int j = 0;
    for(int i = 0 ; i < v1.size() ; i++){
        int tp = 0;
        if(v1[i].type == 1)
            tmp += x1[v1[i].id] - x0[v1[i].id];
        else
            tmp -= x1[v1[i].id] - x0[v1[i].id];
        while(j < v2.size() && cross(v1[i].pt,v2[j].pt) >= 0 )
        {
            if(v2[j].type == 1)
                tmp += x1[v2[j].id] - x0[v2[j].id];
            else
                tmp -= x1[v2[j].id] - x0[v2[j].id];
            j++;
        }
        ans = max(ans, tmp);
    }
    swap(v1,v2);
    tmp = 0LL;
    j = 0;
    for(int i = 0 ; i < v1.size() ; i++){
        int tp = 0;
        if(v1[i].type == 1)
            tmp += x1[v1[i].id] - x0[v1[i].id];
        else
            tmp -= x1[v1[i].id] - x0[v1[i].id];
        while(j < v2.size() && cross(v1[i].pt,v2[j].pt) >= 0 )
        {
            if(v2[j].type == 1)
                tmp += x1[v2[j].id] - x0[v2[j].id];
            else
                tmp -= x1[v2[j].id] - x0[v2[j].id];
            j++;
        }
        ans = max(ans, tmp);
    }
    // cout << ans << "<<<\n";
    return ans;
}

int main(){
    scanf("%d", &n);

    for(int i = 0 ; i < n ; i++){
        scanf("%lld %lld %lld", &x0[i], &x1[i], &y[i]);
        if(x1[i] < x0[i])
            swap(x1[i],x0[i]);
    }

    ll ans = 0LL;
    // solve(110, 40);

    for(int i = 0 ; i < n ; i++){
        ll tmp = x1[i] - x0[i];

        tmp += max(solve(x0[i], y[i]), solve(x1[i], y[i]));

        ans = max(ans, tmp);
    }

    printf("%lld\n", ans);
    
    return 0;
}
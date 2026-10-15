struct Node { 
  ll p, l, r; // p eh a melhor transicao para dp[l],dp[l+1],...,dp[r]
}; 

vc<Node> st; int beg = 0;
dp[0] = 0; st.push_back({0,1,n});
for(int i=1 ; i<=n ; i++){
    dp[i] = f(st[beg].p, i)

    if(st[beg].r == i) beg++;
    else st[beg].l++;
    // enquanto o i atual for melhor transicao eu vou remover esses intervalos inuteis
    while(st.size() > beg && f(i,st.back().l) < f(st.back().p,st.back().l)) st.pop_back();
    // sabemos que para p=i, r = n, so precisamos saber o l
    if(st.size() <= beg) st.push_back(i,i+1,n);
    else{ // busca binaria
        int l = st.back().l, r = st.back().r,ans = l;
        while(l <= r){
            int mid = l + r; mid >>= 1;
            if(f(i,mid) > f(dq.back().p,mid)) ans = mid, r = mid-1
            else l = mid+1;
        }
        dq.back().r = ans;
        if(ans != n) st.push_back({i,ans+1,n});
    }
}

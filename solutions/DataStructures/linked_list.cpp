void test()
{
    list<ll> lista = {0};
    map<int,list<ll> :: iterator> mapa;

    cin >> n;
    mapa[0] = lista.begin();

    for(int i = 1; i <= n; i++){
        int tip;
        cin >> tip;
        if(tip == 1){
            int a;
            cin >> a;
            auto it = mapa[a];
            advance(it, 1);
            mapa[i] = lista.insert(it, i);
        }
        else{
            ll a, b;
            cin >> a >> b;
            
            auto it = mapa[a];
            ll ans = 0;
            while(*it != b){
                ans += *it;
                auto p = it;
                advance(it, 1);
                lista.erase(p);
            }
            cout << ans << '\n';
        }
    }
    for(auto j: lista) cout << j << ' ';
    cout << endl;

}

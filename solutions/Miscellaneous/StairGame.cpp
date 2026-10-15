int main()
{
    int q;
    cin >> q;
    while(q--)
    {
        int n;
        cin >> n;
        int rs = 0;
        for(int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            if(i&1)
                rs ^= x;
        }
        cout << (rs?"first":"second") << '\n';
    }
    return 0;
}
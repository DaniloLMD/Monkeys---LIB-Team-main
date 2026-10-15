struct pair_hash {
    size_t operator()(const pair<int,int>&x)const{
        return hash<ll>()(((ll)x.first)^(((ll)x.second)<<32));
      }
};
unordered_map<pair<int,int>,int,pair_hash> mp;

int main()
{
    //usar o tamanho esperado do umap
    mp.reserve(N*4);
    mp.max_load_factor(0.25);
}
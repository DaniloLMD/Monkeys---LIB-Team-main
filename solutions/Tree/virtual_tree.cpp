// Virtual Tree
//
// Indexado de 1.
// Comprime uma arvore dado um conjunto S de vertices, de forma que
// o conjunto de vertices da arvore comprimida contenha S e seja
// minimal e fechado sobre a operacao de LCA.
// Se |S| = k, a arvore comprimida tem menos que 2k vertices.
//
// O(k log(k))
struct VirtualTree{
    #warning colocar o LCA 

    vector<vector<int>> & graph; // grafo original
    vector<vector<int>> tree; // virtual tree
    int r; // raiz da virtual tree
    int n; // qtd de vertices
    VTLCA lca;

    VirtualTree(int n, vector<vector<int>> & graph) : n(n), graph(graph),tree(n+10),lca(n,graph){
        tree.resize(n+10);
    }

    void build(vector<int> & vtx){
        // ordena pelo tempo de entrada
        sort(vtx.begin(),vtx.end(),[&](int x,int y){
            return lca.tin[x] < lca.tin[y];
        });
        // adiciona os lcas
        int sz = vtx.size();
        for(int i=0; i<sz-1; i++) vtx.push_back(lca.calc_lca(vtx[i],vtx[i+1]));
        sort(vtx.begin(),vtx.end(),[&](int x,int y){
            return lca.tin[x] < lca.tin[y];
        });
        // tira os caras repetidos e limpa a arvore de queries anteriores
        vtx.erase(unique(vtx.begin(),vtx.end()),vtx.end());
        sz = vtx.size();
        for(int i=0; i<sz; i++) tree[vtx[i]].clear();
        
        // arruma as arestas da virtual tree
        vector<int> st;
        st.push_back(vtx[0]);
        r = vtx[0];
        for(int i=1; i<sz; i++){
            while(!lca.lca(st.back(),vtx[i])) st.pop_back();
            
            tree[st.back()].push_back(vtx[i]);
            tree[vtx[i]].push_back(st.back());
            
            st.push_back(vtx[i]);
        }        
    }
};
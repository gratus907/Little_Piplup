struct Disjoint_Set_Union
{
    #define V 101010
    int parent[V], size[V];
    Disjoint_Set_Union(int N = V-1)
    {
        init(N);
    }
    void init(int N)
    {
        for(int i=1;i<=N;i++)
        {
            parent[i]=i;
            size[i]=1;
        }
    }
    int Find(int K)
    {
        while(K!=parent[K])
        {
            parent[K]=parent[parent[K]];
            K=parent[K];
        }
        return K;
    }
    void unite(int x, int y)
    {
        int u=Find(x), v=Find(y);
        if(u==v)
            return;
        if(size[u]>size[v])
            swap(u, v);
        size[v]+=size[u];
        size[u] = 0;
        parent[u] = parent[v];
    }
};

struct Cosaraju
{
    int V, E;
    vector <vector<int>> G;
    vector <vector<int>> rG;
    vector <vector <int>> scc;
    vector <int> dfs_stack;
    vector <bool> visit;
    Cosaraju(int n = 0)
    {
        V = n;
        G.resize(V+5);
        rG.resize(V+5);
        visit.resize(V+5);
        scc.resize(V+5);
    }
    void re_init(int n)
    {
        V = n;
        G.resize(V+5);
        rG.resize(V+5);
        visit.resize(V+5);
        scc.resize(V+5);
    }
    void AddEdge(int u, int v)
    {
        G[u].push_back(v);
        rG[v].push_back(u);
    }
    void dfs(int r)
    {
        visit[r] = true;
        for (auto it:G[r])
            if (!visit[it])
                dfs(it);
        dfs_stack.push_back(r);
    }
    void rev_dfs(int r, int scc_num)
    {
        visit[r] = true;
        scc[scc_num].push_back(r);
        for (auto it:rG[r])
            if (!visit[it])
                rev_dfs(it, scc_num);
    }
    void find_scc()
    {
        fill(all(visit),0);
        for (int i = 1; i<=V; i++)
            if (!visit[i])
                dfs(i);
        fill(all(visit),0);
        int scc_count = 0;
        while(!dfs_stack.empty())
        {
            int tp = dfs_stack.back();
            dfs_stack.pop_back();
            if (!visit[tp])
            {
                rev_dfs(tp, scc_count);
                scc_count++;
            }
        }
        scc.resize(scc_count);
        for (int i = 0; i<scc_count; i++)
            sort(all(scc[i]));
        sort(all(scc),[](vector<int>&a, vector<int>&b)->bool{return a[0]<b[0];});
    }
};

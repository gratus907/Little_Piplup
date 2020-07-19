struct TWOSAT
{
    // Usage : sat.add_clause(a, 1, b, 1);
    // (ind1, val1, ind2, val2)
    struct Cosaraju
    {
        int V, E;
        vector <vector<int>> G;
        vector <vector<int>> rG;
        vector <vector <int>> scc;
        vector <int> whichscc;
        vector <int> dfs_stack;
        vector <bool> visit;
        Cosaraju(int n = 0)
        {
            V = n;
            G.resize(V+5);
            rG.resize(V+5);
            visit.resize(V+5);
            scc.resize(V+5);
            whichscc.resize(V+5);
        }
        void re_init(int n)
        {
            V = n;
            G.resize(V+5);
            rG.resize(V+5);
            visit.resize(V+5);
            scc.resize(V+5);
            whichscc.resize(V+5);
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
            for (int i = 0; i<scc_count; i++)
            {
                for (auto it:scc[i])
                {
                    whichscc[it] = i;
                }
            }
            sort(all(scc),[](vector<int>&a, vector<int>&b)->bool{return a[0]<b[0];});
        }
    };
    Cosaraju C;
    int N, M;
    inline int renumber(int x)
    {
        if (x > N) return x - N;
        else return x + N;
    }
    void build(int NN, int MM)
    {
        N = NN, M = MM;
        C.re_init(2*N+10);
    }
    void acl(int u, int v)
    {
        if (u < 0) u = -u + N;
        if (v < 0) v = -v + N;
        C.AddEdge(renumber(u),v);
        C.AddEdge(renumber(v),u);
    }
    void add_clause(int a, bool aw, int b, int bw)
    {
        if (!aw) a = -a;
        if (!bw) b = -b;
        acl(a, b);
    }
    pair<bool, vector<int>> solve()
    {
        C.find_scc();
        for (int i = 1; i<=N; i++)
        {
            if (C.whichscc[i]==C.whichscc[i+N])
            {
                return {0, {}};
            }
        }
        vector <int> v;
        for (int i = 1; i<=N; i++)
        {
            v.push_back((C.whichscc[i] < C.whichscc[i+N])?1:0);
        }
        return {1, v};
    }
};

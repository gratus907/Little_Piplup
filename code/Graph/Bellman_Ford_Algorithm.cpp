struct Edge
{
    int u, v, w;
};

vector <Edge> edgelist;
int V, E;
int dist[V+1];

bool relax_all_edge()
{
    bool flag = false;
    for (auto it:edgelist)
    {
        int u = it.u, v = it.v, w = it.w;
        if (dist[v] > dist[u] + w && (dist[u]!=INF))
        {
            flag = true;
            dist[v] = dist[u]+w;
        }
    }
    return flag;
}

int bellman_ford()
{
    fill(dist,dist+V+2,INF);
    dist[1] = 0;
    for (int i = 0; i<V-1; i++)
    {
        relax_all_edge();
    }
    if (relax_all_edge())
        return -1;
    else
        return 0;
}

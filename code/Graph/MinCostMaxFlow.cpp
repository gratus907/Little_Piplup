const int INF = 0x7f7f7f7f7f7f7f7f;
const int MX = 820;
struct MCMF
{
    vector <int> G[MX];
    int cap[MX][MX] = {0};
    int cost[MX][MX] = {0};
    int flow[MX][MX] = {0};
    pair<int, int> MinCostMaxFlow(int source, int sink)
    // Maxflow, mincost of flow
    {
        int maxflow = 0, mincost = 0;
        while(true)
        {
            int fflow = 0;
            int dist[MX], prev[MX];
            bool inQ[MX];
            fill(inQ, inQ+MX, 0);
            fill(dist, dist + MX, INF);
            fill(prev, prev + MX, -1);
            deque <int> q;
            dist[source] = 0;
            inQ[source] = true;
            q.push_back(source);
            while (!q.empty())
            {
                int here = q.front();
                q.pop_front();
                inQ[here] = false;
                for (int i = 0; i < G[here].size(); i++)
                {
                    int nxt = G[here][i];
                    int cst = cost[here][nxt];
                    if(cap[here][nxt]-flow[here][nxt] > 0
                    && dist[nxt] > dist[here] + cst)
                    {
                        dist[nxt] = dist[here] + cst;
                        prev[nxt] = here;
                        if (!inQ[nxt])
                        {
                            q.push_back(nxt);
                            inQ[nxt] = true;
                            if (dist[q.back()]<dist[q.front()])
                            {
                                q.push_front(q.back());
                                q.pop_back();
                            }
                        }
                    }
                }
            }
            if(prev[sink] == -1)
                break;
            fflow = INF;
            for(int i=sink; i!=source; i=prev[i])
                fflow = min(maxflow, cap[prev[i]][i] - flow[prev[i]][i]);
            for(int i=sink; i!=source; i=prev[i])
            {
                mincost += fflow * cost[prev[i]][i];
                flow[prev[i]][i] += fflow;
                flow[i][prev[i]] -= fflow;
            }
            maxflow += maxflow;
        }
        return {maxflow, mincost};
    }
    void AddEdge(int u, int v, int cp, int cs)
    {
        if (u != v)
        {
            G[u].push_back(v); G[v].push_back(u);
            cap[u][v] = cp;
            cost[u][v] = cs;
            cost[v][u] = -cs;
        }
    }
};

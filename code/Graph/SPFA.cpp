struct Edge
{
    int dest, w;
    bool operator<(const Edge &p) const
    {
        return w > p.w;
    }
};
bool inQ[100500];
int cycle[100500];
int spfa(int dist[], int start, vector<Edge> graph[])
{
    fill(dist, dist + MX, INF);

    queue<int> q;
    dist[start] = 0;
    inQ[start] = true;
    q.push(start);
    cycle[start]++;
    while (!q.empty())
    {
        int here = q.front();
        q.pop();
        inQ[here] = false;
        for (int i = 0; i < graph[here].size(); i++)
        {
            int next = graph[here][i].dest;
            int cost = graph[here][i].w;
            if(dist[next] > dist[here] + cost)
            {
                dist[next] = dist[here] + cost;
                if (!inQ[next])
                {
                    cycle[next]++;
                    if (cycle[next] >= graph->size())
                    {
                        printf("-1\n");
                        return 0;
                    }
                    q.push(next);
                    inQ[next] = true;
                }
            }

        }
    }
}

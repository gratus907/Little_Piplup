// Optimized SPFA, https://hongjun7.tistory.com/170 , style modifications.
struct Edge
{
    int dest, w;
    bool operator<(const Edge &p) const
    {
        return w > p.w;
    }
};
bool inQ[MX];
void spfa(int dist[], int start, vector<Edge> graph[])
{
    fill(dist, dist + MX, INF);
    deque <int> q;
    dist[start] = 0;
    inQ[start] = true;
    q.push_back(start);
    while (!q.empty())
    {
        int here = q.front();
        q.pop_front();
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
                    q.push_back(next);
                    inQ[next] = true;
                    if (dist[q.back()]<dist[q.front()])
                    {
                        q.push_front(q.back());
                        q.pop_back();
                    }
                }
            }
        }
    }
}

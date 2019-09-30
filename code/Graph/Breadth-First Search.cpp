#include <bits/stdc++.h>

queue <int> q;

int adj[1010][1010];
int bfs_visit[1010];
void bfs(int i)
{
    q.push(i);
    bfs_visit[i] = 1;
    while (!q.empty())
    {
        int cur = q.front();
        printf("%d ", cur);
        q.pop();
        for (int u = 1; u <= 1010; u++)
        {
            if (adj[cur][u] && !bfs_visit[u])
            {
                bfs_visit[u] = 1;
                q.push(u);
            }
        }
    }
}
int main()
{
    int V, E, r;
    scanf("%d%d%d", &V, &E, &r);
    while (E--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a][b] = 1;
        adj[b][a] = 1;
    }
    bfs(r);
}

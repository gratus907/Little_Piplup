//Original Author : https://plzrun.tistory.com/

int r[V][V]; // flow capacity
bool chk[V][V]; // edge existence
int level[V];
vector<int> v[V];
queue<int> q;

bool bfs(int src, int sink)
{
    memset(level,-1,sizeof(level));
    level[src]=0;
    q.push(src);
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int y: v[x])
        {
            if(r[x][y]>0 && level[y]<0) {
                level[y]=level[x]+1;
                q.push(y);
            }
        }
    }
    return level[sink]>=0;
}

int work[V];

int dfs(int x, int sink, int f)
{
    if(x==sink) return f;
    for(int &i=work[x]; i<v[x].size(); i++)
    {
        int y=v[x][i];
        if(level[y]>level[x] && r[x][y]>0)
        {
            int t = dfs(y,sink,min(f,r[x][y]));
            if(t>0)
            {
                r[x][y]-=t;
                r[y][x]+=t;
                return t;
            }
        }
    }
    return 0;
}

int dinic(int src, int sink)
{
    int flow=0;
    while(bfs(src,sink))
    {
        int f=0;
        memset(work,0,sizeof(work));
        while((f=dfs(src,sink,INT_MAX))>0)
            flow+=f;
    }
    return flow;
}

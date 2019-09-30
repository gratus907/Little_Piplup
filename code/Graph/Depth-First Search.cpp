//Works on adjacent list (array-of-vector).
vector <int> graph[V];
void dfs(int root)
{
    visited[root] = 1;
    for (auto it:graph[root])
    {
        if (!visited[it])
            dfs(it);
    }
    sorted.push_back(root);
}

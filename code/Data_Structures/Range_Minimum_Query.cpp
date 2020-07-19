struct Segtree
{
    int n;
    vector<int> segtree;

    Segtree(const vector<int> &data)
    {
        n = data.size();
        segtree.resize(4 * n);
        initialize(data, 0, n - 1, 1);
    }

    int initialize(const vector<int> &data, int l, int r, int node)
    {
        if (l == r)
            return segtree[node] = data[l];
        int mid = (l + r) / 2;
        int lmin = initialize(data, l, mid, node * 2);
        int rmin = initialize(data, mid + 1, r, node * 2 + 1);
        return segtree[node] = min(lmin, rmin);
    }
    int query(int l, int r, int node, int nodeleft, int noderight)
    {
        if (r < nodeleft || noderight < l)
            return INT_MAX;
        if (l <= nodeleft && noderight <= r)
            return segtree[node];
        int mid = (nodeleft + noderight) / 2;
        return min(query(l,r,node*2,nodeleft,mid),
        query(l,r,node*2+1,mid+1,noderight));
    }
    void update(int left,int right,int node, int change_node ,int diff)
    {
        if (!(left <= change_node &&change_node <= right))
            return;
        if (left == right)
        {
            segtree[node] += diff;
        }
        if (left != right)
        {
            int mid = (left + right) / 2;
            update(left, mid, node * 2, change_node, diff);
            update(mid +1,right, node * 2 +1, change_node, diff);
            segtree[node] = min(segtree[node*2], segtree[node*2+1]);
        }
    }
    void update(int change_node, int diff)
    {
        update(0,n-1,1,change_node,diff);
    }
    void update_to(int change_node, int to)
    {
        int u = sumq(change_node, change_node);
        update(change_node, to-u);
    }
};

// min : BOJ 6171. max : BOJ 12795
struct SEG
{
    int n;
    vector<int> segtree;
    SEG(){}
    SEG(const vector<int> &data)
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
        int ls = initialize(data, l, mid, node * 2);
        int rs = initialize(data, mid + 1, r, node * 2 + 1);
        return segtree[node] = ls+rs;
    }
    int sumq(int l, int r, int node, int nodeleft, int noderight)
    {
        if (r < nodeleft || noderight < l)
            return 0;
        if (l <= nodeleft && noderight <= r)
            return segtree[node];
        int mid = (nodeleft + noderight) / 2;
        return sumq(l,r,node*2,nodeleft,mid)+
        sumq(l,r,node*2+1,mid+1,noderight);
    }
    int findkth(int node, int l, int r, int target)
    {
        if (l == r) return l;
        int lft = segtree[node*2];
        if (lft >= target) return findkth(node*2, l, (l+r)/2, target);
        else return findkth(node*2+1, (l+r)/2+1, r, target-lft);
    }
    void update(int left, int right,int node, int change_node ,int diff)
    {
        if (!(left <= change_node &&change_node <= right))
            return;
        segtree[node] += diff;
        if (left != right)
        {
            int mid = (left + right) / 2;
            update(left, mid, node * 2, change_node, diff);
            update(mid +1,right, node * 2 +1, change_node, diff);
        }
    }

    // WRAPPER FUNCTIONS
    int sumq(int l, int r)
    {
        return sumq(l, r, 1, 0, n-1);
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
    int findkth(int target)
    {
        return findkth(1, 0, n-1, target);
    }
};

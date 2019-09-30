void update(int left,int right,int node, int change_node ,int diff)
{
    if (!(left <= change_node &&change_node <= right))
        return; //No effect on such nodes.
    tree[node] += diff; // This part must be changed with tree function.
    if (left != right)
    {
        int mid = (left + right) / 2;
        update(left, mid, node * 2, change_node, diff);
        update(mid +1,right, node * 2 +1, change_node, diff);
    }
}

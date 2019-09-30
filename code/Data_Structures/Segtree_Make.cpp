int arr[SIZE];
int tree[TREE_SIZE];
int makeTree(int left,int right,int node)
{
    if (left == right)
        return tree[node] = arr[left];
    int mid = (left + right) / 2;
    tree[node] += makeTree(left, mid, node * 2);
    tree[node] += makeTree(mid + 1,right, node * 2 +1);
    return tree[node];
}

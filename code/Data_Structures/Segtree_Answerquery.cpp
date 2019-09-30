/*
Our Search range : start to end
Node has range left to right
We may answer query in O(log n) time.
*/
int Query(int node, int left, int right, int start, int end)
{
    if (right < start || end < left)
        return 0; //Node is out of range
    if (start <= left && right <= end)
        return tree[node]; //If node is completely in range
    int mid = (left + right) / 2;
    return Query(node * 2, left, mid, start, end)
    +Query(node*2+1,mid+1,right,start,end);
}

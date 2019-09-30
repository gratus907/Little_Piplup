vector <int> sequence;
vector <int> L;
int lis_len;
int position[BIG];
int lis[BIG];
int lis_pushed[BIG];
int n;
void FindLIS(vector <int> &seq)
{
    L.push_back(seq[0]);
    position[0] = 0;
    for (int i = 1; i<n; i++)
    {
        int u = L.size();
        if (seq[i] > L[u-1])
        {
            position[i] = u;
            L.push_back(seq[i]);
        }
        else
        {
            int pos = lower_bound(L.begin(),L.end(),seq[i])-L.begin();
            L[pos] = seq[i];
            position[i] = pos;
        }
    }
    lis_len=L.size();
    int lookingfor = lis_len-1;
    for (int i = n-1; i>=0; i--)
    {
        if (lis_pushed[position[i]]==0 && lookingfor == position[i])
        {
            lis[position[i]] = seq[i];
            lis_pushed[position[i]]=1;
            lookingfor--;
        }
    }
}

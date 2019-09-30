vector <int> sequence;
int n, lislen;
multiset<int> increase;

void find_lis()
{
    for (int i = 0; i<n; i++)
    {
        auto it = lower_bound(all(increase),sequence[i]);
        if (it == increase.begin())
            increase.insert(sequence[i]);
        else
        {
            --it;
            increase.erase(it);
            increase.insert(sequence[i]);
        }
    }
    lislen = increase.size();
}

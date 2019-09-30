int Binom(int n, int k)
{
    if (n < k)
        return 0;
    if (k == n || k == 0)
        return 1;
    int res = 1;
    if ( k > n - k )
        k = n - k;
    for (int i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

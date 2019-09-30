int p[BIGNUM];
bool is_composite[BIGNUM];
void sieve()
{
    for (int i = 2; i <= BIGNUM; i++)
    {
        if (!is_composite[i])
        {
            p[pcount++] = i;
            for (int j = i * 2; j <= BIGNUM; j += i)
                is_composite[j] = true;
        }
    }
}

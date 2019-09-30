const ll MOD = BIG_PRIME;
int L;
char S[STR_LEN];
int safemod(int n)
{
    if(n >= 0)
        return n % MOD;
    return ((-n/MOD+1)*MOD + n) % MOD;
}
vector <int> hashmap[MOD];
void Rabin_Karp(int len)
{
    int Hash = 0;
    int pp = 1;
    for(int i=0; i<=L-len; i++)
    {
        if(i == 0)
        {
            for(int j = 0; j<len; j++)
            {
                Hash = safemod(Hash + S[len-j-1]*pp);
                if(j < len-1)
                    pp = safemod(pp*2);
            }
        }
        else
            Hash = safemod(2*(Hash - S[i-1]*pp) + S[len+i-1]);
        hashmap[Hash].push_back(i);
    }
    return;
}

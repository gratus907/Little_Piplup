struct Trie
{
    int trie[NODE_MAX][CHAR_N];
    int nxt = 1;
    void insert(const char* s)
    {
        int k = 0;
        for (int i = 0; s[i]; i++)
        {
            int t = s[i] - 'a';
            if (!trie[k][t])
            {
                trie[k][t] = nxt;
                nxt++;
            }
            k = trie[k][t];
        }
        trie[k][26] = 1;
    }
    bool find(const char* s, bool exact = false)
    {
        int k = 0;
        for (int i = 0; s[i]; i++)
        {
            int t = s[i] - 'a';
            if (!trie[k][t])
                return false;
            k = trie[k][t];
        }
        if (exact)
        {
            return trie[k][26];
        }
        return true;
    }
};
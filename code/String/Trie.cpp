const int MAX_NODES = 26;
inline int getnext(char x)
{
    return x-'a';
}
struct Trie
{
    Trie *next[MAX_NODES];
    int cnt;
    bool ends;
    Trie()
    {
        fill(next, next+MAX_NODES, nullptr);
        cnt = ends = 0;
    }
    ~Trie()
    {
        for (auto &it:next)
            if (it) delete it;
    }
    void insert(char *str)
    {
        if (*str==0)
            ends = true;
        else
        {
            int nxt = getnext(*str);
            if (!next[nxt])
            {
                next[nxt] = new Trie();
                cnt++;
            }
            next[nxt]->insert(str+1);
        }
    }
    int query(char* str, int k)
    {
        if (*str == 0)
            return k;
        else
        {
            if (cnt > 1 || ends)
                k++;
            int nxt = getnext(*str);
            return next[nxt]->query(str+1, k);
        }
    }
};

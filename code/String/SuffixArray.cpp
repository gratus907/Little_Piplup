const int SMAX = 505050;
struct SuffixArray
{
    // SuffixArray in n log n time
    // Code originally from https://blog.naver.com/kks227/
    SuffixArray(string S = ""){ str = S; };
    void init(string S)
    {
        str = S;
    }
    string str;
    int n;
    int SA[SMAX], pos[SMAX], LCP[SMAX];
    struct suffixNode
    {
        int sa;
        pii rank;
        bool operator<(const suffixNode &other)
        {
            return rank < other.rank;
        }
    };

    vector<suffixNode> node, tmp;

    void constructSA()
    {
        n = str.length();
        node.resize(SMAX);
        tmp.resize(SMAX);
        for (int i = 0; i<n; i++)
        {
            node[i].sa = i;
            int snd = (i<n-1 ? str[i+1]-'a' : -1);
            node[i].rank = {str[i]-'a', snd};
        }
        sort(node.begin(), node.begin()+n);
        for (int d = 2; d<n; d*=2)
        {
            int m = 0, tp = node[0].rank.first;
            node[0].rank.first = pos[node[0].sa] = 0;
            for (int i = 1; i<n; i++)
            {
                if (pii(tp, node[i-1].rank.second) == node[i].rank)
                    node[i].rank.first = m;
                else
                {
                    tp = node[i].rank.first;
                    node[i].rank.first = ++m;
                }
                pos[node[i].sa] = i;
            }
            vector <int> cnt(m+5, 0);
            m++;
            for (int i = 0; i<n; i++)
            {
                int j = node[i].sa+d;
                node[i].rank.second = (j<n ? node[pos[j]].rank.first : -1);
                cnt[node[i].rank.second+1]++;
            }
            for (int i = 1; i<=m; i++)
                cnt[i] += cnt[i-1];
            for (int i = n-1; i>=0; i--)
                tmp[--cnt[node[i].rank.second+1]] = node[i];

            fill(all(cnt), 0);
            for (int i = 0; i<n; i++)
                cnt[tmp[i].rank.first]++;
            for (int i = 1; i<m; i++)
                cnt[i] += cnt[i-1];
            for (int i = n-1; i>=0; i--)
                node[--cnt[tmp[i].rank.first]] = tmp[i];
        }
        for (int i = 0; i < n; i++)
        {
            SA[i] = node[i].sa;
            pos[SA[i]] = i;
        }
    }

    void constructLCP()
    {
        for (int i = 0, k = 0; i<n; i++, k = max(k-1, 0))
        {
            if (pos[i] == n-1) continue;
            for (int j = SA[pos[i]+1]; str[i+k]==str[j+k]; k++);
            LCP[pos[i]] = k;
        }
    }
};

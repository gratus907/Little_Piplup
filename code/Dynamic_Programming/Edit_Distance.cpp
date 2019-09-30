int edit_dist[1010][1010];
int Editdist(string &s, string &t)
{
    int slen = s.length();
    int tlen = t.length();
    for (int i = 1; i<=slen; i++)
        edit_dist[i][0] = i;
    for (int i = 1; i<=tlen; i++)
        edit_dist[0][i] = i;
    for (int i = 1; i<=tlen; i++)
    {
        for (int j = 1; j<=slen; j++)
        {
            if (s[j-1]==t[i-1])
                edit_dist[j][i] = edit_dist[j-1][i-1];
            else
                edit_dist[j][i] = min(edit_dist[j-1][i]+1,
                    min(edit_dist[j-1][i-1]+1,edit_dist[j][i-1]+1));
        }
    }
    return edit_dist[slen][tlen];
}

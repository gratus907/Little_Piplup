int d[120][120];
int n;
void Floyd_Warshall()
{
    fill(d, d+sizeof(d),INF);
    //---Edges Here---//
    for (int i = 1; i<=n; i++)
        for (int j = 1; j<=n; j++)
            for (int k = 1; k<=n; k++)
                d[j][k] = MIN(d[j][k],d[j][i]+d[i][k]);
}

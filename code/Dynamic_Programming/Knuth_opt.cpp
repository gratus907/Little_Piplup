for(i = 1; i <= n; i++)
{
    dp[i][i] = 0;
    p[i][i] = i;
}

for(j = 2; j <= n; j++)
{
    for(i = 1; i <= n-j+1; i++){
        s = i, e = i+j-1;
        dp[s][e] = vMax;
        for(k = p[s][e-1]; k <= p[s+1][e]; k++)
        {
            if(dp[s][e] > dp[s][k] + dp[k+1][e])
            {
                dp[s][e] = dp[s][k] + dp[k+1][e];
                p[s][e] = k;
            }
        }
        dp[s][e] += cost[s][e];
    }
}

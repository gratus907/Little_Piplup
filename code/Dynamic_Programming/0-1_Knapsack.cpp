int dp[N][W];
int weight[N];
int value[N];
void knapsack()
{
    for (int i = 1; i<=n; i++)
    {
        for (int j = 0; j<=W; j++)
            dp[i][j] = dp[i-1][j];
        for (int j = weight[i]; j<=W; j++)
            dp[i][j] = max(dp[i][j], dp[i-1][j-weight[i]]+value[i]);
    }
}

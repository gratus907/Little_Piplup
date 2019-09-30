def coin_change(n, coins):
    parts = [1]+[0]*n
    for c in coins:
        for i, x in enumerate(range(c, n+1)):
            parts[x] += parts[i]
    return parts[n]

int dist (Point &p, Point &q)
{
    return (p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y);
}

bool compare(Point &p, Point &q)
{
    return (p.x < q.x);
}

bool ycompare(Point &p, Point &q)
{
    return (p.y<q.y);
}
Point pts[101010];

int closest_pair(Point p[], int n)
{
    //printf("%p call %d\n",p,n);
    if (n==2)
    {
        return dist(p[0], p[1]);
    }
    if (n==3)
    {
        return min(dist(p[0],p[1]),
        min(dist(p[1],p[2]),dist(p[0],p[2])));
    }
    Point mid[n];
    int line = (p[n/2 - 1].x + p[n/2].x) / 2;
    int d = min(closest_pair(p, n/2), closest_pair(p + n/2, n - n/2));
    int pp = 0;
    for (int i = 0; i < n; i++)
    {
        int t = line - p[i].x;
        if (t*t < d)
        {
            mid[pp] = p[i];
            pp++;
        }
    }
    sort(mid,mid+pp,ycompare);
    for (int i = 0; i < pp - 1; i++)
        for (int j = i + 1; j < pp && mid[j].y - mid[i].y < d; j++)
            d = min(d, dist(mid[i], mid[j]));
    return d;
}

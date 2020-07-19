struct point
{
    int x, y, dx, dy;
    point operator+(const point &other)
    {
        return {x+other.x, y+other.y};
    }
    point operator-(const point &other)
    {
        return {x-other.x, y-other.y};
    }
    point operator*(const int C)
    {
        return {x*C, y*C, dx, dy};
    }
    int normsq()
    {
        return x*x+y*y;
    }
};

int dist(point &a, point &b)
{
    return (a-b).normsq();
}
class convex_hull
{
public:
    int n;
    static int ccw (point a, point b, point c)
    {
        int v = (b.x - a.x) * (c.y - a.y) - (b.y-a.y)*(c.x-a.x);
        if (v > 0) return 1;
        if (!v) return 0;
        return -1;
    }
    static bool compy (point &a, point &b)
    {
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    }
    vector <point> pt;
    vector <point> convex;
    void graham_scan()
    {
        convex.clear();
        sort(all(pt), compy);
        point down = pt[0];
        sort(all(pt), [&down](auto a, auto b)
        {
            int u = ccw(down, a, b);
            if (u!=0) return u>0;
            else return dist(down, a) < dist(down, b);
        });
        convex.push_back(pt[0]);
        convex.push_back(pt[1]);
        for (int i = 2; i<n; i++)
        {
            while(convex.size() > 1)
            {
                point tp = convex.back();
                convex.pop_back();
                point tptp = convex.back();
                if (ccw(tptp,tp,pt[i]) > 0)
                {
                    convex.push_back(tp);
                    break;
                }
            }
            convex.push_back(pt[i]);
        }
    }
    void rotating_calipers()
    // a, b : Furthest distance point
    {
        int msz = 0;
        int t = 0;
        point o = {0, 0};
        int nc = convex.size();
        point a = convex[0], b = convex[0];
        for(int i=0; i<convex.size(); i++)
        {
            while(t+1 < convex.size() &&
            ccw(o, convex[i+1]-convex[i], convex[t+1]-convex[t])>=0)
            {
                if (msz < dist(convex[i], convex[t]))
                {
                    msz = dist(convex[i], convex[t]);
                    a = convex[i], b = convex[t];
                }
                t++;
            }
            if (msz < dist(convex[i], convex[t]))
            {
                msz = dist(convex[i], convex[t]);
                a = convex[i], b = convex[t];
            }
        }
        printf("%lld %lld %lld %lld\n",a.x,a.y,b.x,b.y);
    }
};

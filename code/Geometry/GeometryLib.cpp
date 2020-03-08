bool equal(double a, double b, double tol = 1e-12)
{
    return abs(a-b)<=tol;
}

struct point
{
    double x, y;
    point operator+(const point &other)
    {
        return {x+other.x, y+other.y};
    }
    point operator-(const point &other)
    {
        return {x-other.x, y-other.y};
    }
    point operator*(const double C)
    {
        return {x*C, y*C};
    }
    double normsq()
    {
        return x*x+y*y;
    }
};

double normsq(point a)
{
    return a.x*a.x+a.y*a.y;
}
double inner(point a, point b)
{
    return a.x*b.x+a.y*b.y;
}
double cross(point a, point b)
{
    return a.x*b.y-a.y*b.x;
}
struct line_segment
{
    point a, b;
    double lensq()
    {
        return normsq(b-a);
    }
};
double point_segment_dist_square(point &p, line_segment &L, double &t, point &pt)
{
    double dx = L.b.x-L.a.x, dy = L.b.y-L.a.y;
    point dp = p-L.a;
    double seglensq = normsq({dx, dy});
    if (equal(seglensq,0))
    {
        pt = L.a;
        t = 0;
        return (normsq(dp));
    }
    else
    {
        t = inner(dp, {dx, dy})/seglensq;
        if (t <= eps)
        {
            if (t >= -eps)
                t = 0;
            pt = L.a;
        }
        else if (t >= (1-eps))
        {
            if (t <= (1+eps))
                t = 1;
            pt = L.b;
        }
        else
            pt = (L.a*(1.0-t))+L.b*t;
        return (normsq(pt-p));
    }
}

double seg_seg_dist_square(line_segment L1, line_segment L2, point &inter)
{
    double dummy;
    point dummyp;
    double seglen1 = L1.lensq(), seglen2 = L2.lensq();
    if (seglen1 > seglen2)
    {
        swap(L1, L2);
        swap(seglen1, seglen2);
    }
    double t = 0;
    double mindist = 1e20;
    if (seglen1 <= eps)
    {
        inter = L1.a;
        if (seglen2 <= eps)
            mindist = normsq(L2.a-L1.a);
        else
            mindist = point_segment_dist_square(L1.a, L2, dummy, dummyp);
        return mindist;
    }
    double d = cross(L1.a-L1.b, L2.a-L2.b);
    bool par = equal(d, 0);
    if (!par)
    {
        t = 1 - cross(L2.b-L1.b, L2.b-L2.a)/d;
        double tps = sqrt(eps/seglen1);
        if (t >= -tps && t <= (1+tps))
        {
            double s = 1-cross(L1.a-L1.b,L2.b-L2.a)/d;
            double tps2 = sqrt(eps/seglen2);
            if (s >= -tps2 && s <= (1+tps2))
            {
                mindist = 0;
                inter = L1.a*(1-t)+L1.b*t;
                return mindist;
            }
        }
    }

    mindist = point_segment_dist_square(L2.a, L1, t, inter);
    double md2 = point_segment_dist_square(L2.b, L1, t, dummyp);
    if (md2 < mindist)
    {
        inter = dummyp;
        mindist = md2;
    }
    md2 = point_segment_dist_square(L1.b, L2, t, dummyp);
    if (md2 < mindist)
    {
        inter = dummyp;
        mindist = md2;
    }
    md2 = point_segment_dist_square(L1.a, L2, t, dummyp);
    if (md2 < mindist)
    {
        inter = dummyp;
        mindist = md2;
    }
    return mindist;
}


double point_segment_dist_square(point &p, line_segment &L, double &dist, point &pt)
{
    double dx = L.b.x-L.a.x, dy = L.b.y-L.a.y;
    point dp = p-L.a;
    double seglensq = normsq({dx, dy});
    if (equal(seglen,0))
    {
        pt = L.a;
        t = point_distance_square(L.a, p);
        return (normsq(dp));
    }
    else
    {
        t = inner(dp, {dx, dy})/seglensq;
    }
}

struct line
{
    double slope, y;
    double left, right;
    pair<double, bool> eval_x(double target_y)
    {
        if (slope == 0 && target_y != y)
            return {0, false};
        double x = (target_y-y)/slope;
        bool t = (left <= x && x <= right);
        return {x, t};
    }
    pair<double, bool> eval_y(double target_x)
    {
        bool t = (left <= target_x && target_x <= right);
        return {slope*target_x+y, t};
    }
};

line segment_line(point a, point b)
{
    if (b.x-a.x == 0)
        return {1e100,-1e100*a.x, min(a.x, b.x), max(a.x, b.x)};
    double s = (b.y-a.y)/(b.x-a.x);
    double yy = a.y-a.x*s;
    return {s, yy, min(a.x, b.x), max(a.x, b.x)};
}
double ang(point p)
{
    return atan2(p.x, -1 * p.y);;
}
struct polygon
{
    vector <point> pt;
    double S;
    bool calc = false;
    void move(point new_zero)
    {
        for (int i = 0; i<pt.size(); i++)
            pt[i] = pt[i]-new_zero;
    }
    void sort_point()
    {
        auto cmp_angle = [](point &a, point &b) -> bool
        {
            return ang(a) < ang(b);
        };
        sort(all(pt),cmp_angle);
    }
    double area(bool pr = false)
    {
        if (calc)
            return S;
        sort_point();
        double A = 0;
        int n = pt.size();
        pt.push_back(pt[0]);
        for (int i = 0; i<n; i++)
            A += (pt[i].x*pt[i+1].y-pt[i].y*pt[i+1].x);
        pt.pop_back();
        calc = true;
        return S = abs(A/2);
    }
    void print()
    {
        for (auto it:pt)
            printf("(%.4lf, %.4lf)\n",it.x,it.y);
    }
};

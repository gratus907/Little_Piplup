//Is 3 points Counterclockwise? 1 : -1
//0 : on same line
int CCW(Point a, Point b, Point c)
{
    int op = a.x*b.y + b.x*c.y + c.x*a.y;
    op -= (a.y*b.x + b.y*c.x + c.y*a.x);
    if (op > 0)
        return 1;
    else if (op == 0)
        return 0;
    else
        return -1;
}

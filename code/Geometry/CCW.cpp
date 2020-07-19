//Is 3 points Counterclockwise? 1 : -1
//0 : on same line
int ccw (point a, point b, point c)
{
    int v = (b.x - a.x) * (c.y - a.y) - (b.y-a.y)*(c.x-a.x);
    if (v > 0) return 1;
    if (!v) return 0;
    return -1;
}

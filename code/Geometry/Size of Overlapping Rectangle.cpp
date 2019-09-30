/*
Function returns size of overlapping rectangle. Given a lot of rectangle in
rec[Numberofrec][4] as [x0,y0,x1,y1]...

Note that function receives and returns int value (overflow check needed!)
*/

int overlapping_rectangle_size()
{
    int left=-INFINITY,right=INFINITY,up=INFINITY,down=-INFINITY;
    int rec[NumberofRec][4];
    for (int i = 0; i<n; i++)
    {
        left = MAX(left,rec[i][0]);
        right = MIN(right,rec[i][2]);
        up = MIN(up,rec[i][3]);
        down = MAX(down,rec[i][1]);
    }
    if (right-left <= 0)
        return 0;
    if (up-down <= 0)
        return 0;
    return (right-left)*(up-down);
}

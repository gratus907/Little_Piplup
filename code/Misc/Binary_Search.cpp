//Finding minimum value with chk() == true
while(lo+1 < hi)
{
    int mid = (lo+hi)/2;

    if(chk(mid))
        lo = mid;
    else
        hi = mid;
}

ll euler_phi(ll n)
{
    ll p=2;
    ll ephi = n;
    while(p*p<=n)
    {
        if (n%p == 0)
            ephi = ephi/p * (p-1);
        while(n%p==0)
            n/=p;
        p++;
    }
    if (n!=1)
    {
        ephi /= n;
        ephi *= (n-1);
    }
    return ephi;
}

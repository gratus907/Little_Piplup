#define sz(v) ((int)(v).size())
typedef int base;
typedef vector <int> vi;
typedef vector <base> vb;

void fft(vb &a, bool invert)
{
    int n = sz(a);
    for (int i = 1, j=0; i<n; i++)
    {
        int bit = n>>1;
        for (; j>=bit; bit>>=1)
        {
            j -= bit;
        }
        j += bit;
        if (i < j)
            swap(a[i],a[j]);
    }
    vector<base> root(n/2);
    int ang = modpow(3, (mod - 1) / n);
    if(invert) ang = modpow(ang, mod - 2);
    root[0] = 1;
    for(int i = 1; i<n/2; i++) root[i] = (root[i-1]*ang)%mod;
    for (int len = 2; len <= n; len <<= 1)
    {
        int step = n / len;
        for (int i = 0; i<n; i+= len)
        {
            for (int j = 0; j<len/2; j++)
            {
                base u = a[i+j], v = (a[i+j+len/2]*root[step*j])%mod;
                a[i+j] = (u+v)%mod;
                a[i+j+len/2] = (u-v)%mod;
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i<n; i++)
            a[i] = frac(a[i],n);
    }
    for (int i = 0; i<n; i++)
        a[i] = (a[i]+10*mod)%mod;
}

void multiply(const vi &a, const vi &b, vi &res_)
{
    vector <base> fa(all(a)), fb(all(b));
    int n = 1;
    while(n < max(sz(a),sz(b)))
        n <<= 1;
    n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,0), fft(fb,0);
    for (int i = 0; i<n; i++)
        fa[i] = (fa[i]*fb[i]+mod)%mod;
    fft(fa,1);
    res_.resize(n);
    for (int i = 0; i<n; i++)
        res_[i] = (fa[i]+mod)%mod;
}
